#include "woody.h"

static int		open_file(t_pars *pam)
{
	if ((pam->src_fd = open(pam->fname, O_RDONLY)) < 0)
		return (error_input(pam->execname, pam->fname, NO_RGHT));
	if ((pam->dst_fd = open(EXEC_NAME, O_CREAT | O_WRONLY, 0755)) < 0)
	{
		printf("Couldn't open %s\n", EXEC_NAME);
		return (-1);
	}
	return (0);
}

static int		read_file(t_pars *pam)
{
	int		off;
	int		len;

	off = 0;
	len = lseek(pam->src_fd, 0, SEEK_END);
	pam->len = len;
	if (!(pam->content = (uint8_t *)malloc(sizeof(uint8_t) * len)))
		return (-1);
	len = lseek(pam->src_fd, 0, SEEK_SET);
	while ((len = read(pam->src_fd, pam->content + off, BUFFLEN)) > 0)
		off += len;
	return (0);
}

uint8_t			ascii_to_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}
/*
static int		find_pattern(const uint8_t *ptr, uint64_t pattern, int size)
{
	int		i;
	uint64_t	*tmp;

	tmp = 0;
	for (i = 0; i < size; i++)
	{
		tmp = (uint64_t*)&ptr[i];
		if (*tmp == pattern)
			return (i);
	}
	return (-1);
}*/

static int		find_pattern32(const uint8_t *ptr, uint32_t pattern, int size)
{
	int		i;
	uint32_t	*tmp;

	tmp = 0;
	for (i = 0; i < size; i++)
	{
		tmp = (uint32_t*)&ptr[i];
		if (*tmp == pattern)
			return (i);
	}
	return (-1);
}

/*
 *	set memory content at "offset" to the value "addr"
*/
static void		patch_addr(t_pars *pam, uint32_t addr, int offset)
{
	uint32_t		*res;

	res = (uint32_t*)(pam->content + pam->off_gap + POFF + offset);
	*res = addr;
}

static void		patch_len(t_pars *pam, uint32_t len, int offset)
{
	uint32_t		*res;

	res = (uint32_t*)(pam->content + pam->off_gap + POFF + offset);
	*res = len;
}

static void		patch(t_pars *pam)
{
	int				offset;
	EHDR			*temp;
	unsigned int	relative_val;

	temp = (EHDR*)pam->content;
	temp->e_entry = pam->off_gap + pam->memory_offset + pam->seg.p_vaddr - pam->seg.p_offset;
	relative_val = 19;
	for (int i = 0; i < MSIZE; i++)
	{
		if (pam->content[pam->off_gap + i] == 0xe9)
			memcpy(pam->content + pam->off_gap + i + 1, &relative_val, sizeof(int));
	}
	for (int i = 0; i < ESIZE; i++)
	{
		if (pam->content[pam->off_gap + EOFF + i] == 0xe9)
		{
			relative_val = 0xBABABA;
			if (pam->memory_offset == 0)
				relative_val = pam->hdr.e_entry - (pam->seg.p_vaddr + pam->seg.p_filesz + GSIZE + 1);
			else
				relative_val = pam->hdr.e_entry - (pam->new_seg->p_vaddr + GSIZE);
			memcpy(pam->content + pam->off_gap + EOFF + i + 1, &relative_val, sizeof(int));
		}
	}
	if ((offset = find_pattern32(pam->content + pam->off_gap + POFF, 0xAAAAAAAA, PSIZE)) < 0)
		printf("0xAAAAAAAA not found\n");
	//printf("Decription offset 0x%X\n", temp->e_entry - pam->hdr.e_entry + (pam->sect.sh_offset - pam->hdr.e_entry));
	//patch_addr(pam, temp->e_entry - pam->hdr.e_entry + (pam->sect.sh_offset - pam->hdr.e_entry)/* - pam->memory_offset*/, offset);
	patch_addr(pam, temp->e_entry - pam->sect.sh_offset/* - pam->memory_offset*/, offset);
	if ((offset = find_pattern32(pam->content + pam->off_gap + POFF, 0xBBBBBBBB, PSIZE)) < 0)
		printf("0xBBBBBBBB not found\n");
	patch_len(pam, pam->sect.sh_size, offset);
	if ((offset = find_pattern32(pam->content + pam->off_gap + POFF, 0xCCCCCCCC, PSIZE)) < 0)
		printf("0xCCCCCCCC not found\n");
	patch_addr(pam, MSIZE + PSIZE + RSIZE + ESIZE, offset);
	if ((offset = find_pattern32(pam->content + pam->off_gap + POFF, 0xDDDDDDDD, PSIZE)) < 0)
		printf("0xDDDDDDDD not found\n");
	patch_len(pam, pam->klen, offset);
}

static void		encrypt(t_pars *pam)
{
	rc4(pam->content + pam->sect.sh_offset + (pam->memory_offset == 0 ? 0 : sizeof(EPHR)), pam->sect.sh_size, pam->key, pam->klen);
}

int				write_payload(t_pars *pam)
{
	int			j;
	uint8_t		byte = 0;
	const char	*payload = PAYLOAD;

	j = 0;
	for (int i = 0; (unsigned long)i < sizeof(PAYLOAD); i++)
	{
		byte = byte << 4;
		byte |= ascii_to_hex(payload[i]);
		if (i % 2 == 1)
		{
			*(pam->content + pam->off_gap + j) = byte;
			byte = 0;
			j++;
		}
	}
	return (0);
}

void			write_shellcode(t_pars *pam, const uint8_t *shellcode, int size, int offset)
{
	int			i;
	int			j;
	uint8_t		byte = 0;

	i = 0;
	j = 0;
	for (i = 0; i < size; i++)
	{
		byte = byte << 4;
		byte |= ascii_to_hex(shellcode[i]);
		if (i % 2 == 1)
		{
			*(pam->content + offset + j) = byte;
			byte = 0;
			j++;
		}
	}
}

int				woody(t_pars pam)
{
	int			len;

	if (open_file(&pam) < 0)
		return (-1);
	if (read_file(&pam) == -1)
		return (-1);
	if (check_elf(&pam) == -1)
		return (-1);
	if ((len = find_gap(&pam, pam.hdr)) < GSIZE)
	{
		expand(&pam);
		memcpy(pam.content, &pam.hdr, sizeof(EHDR));
	}
	write_shellcode(&pam, (uint8_t*)MESSAGE, sizeof(MESSAGE), pam.off_gap);
	write_shellcode(&pam, (uint8_t*)PREP, sizeof(PREP), pam.off_gap + POFF);
	write_shellcode(&pam, (uint8_t*)RC4, sizeof(RC4), pam.off_gap + ROFF);
	write_shellcode(&pam, (uint8_t*)END, sizeof(END), pam.off_gap + EOFF);
	ft_memcpy(pam.content + pam.off_gap + KOFF, pam.key, pam.klen);
	encrypt(&pam);
	patch(&pam);
	write(pam.dst_fd, pam.content, pam.len);
	return (0);
}
