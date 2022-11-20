#include "woody.h"

static int		open_file(t_pars *pam)
{
	if ((pam->src_fd = open(pam->fname, O_RDONLY)) < 0)
		return (error_input(pam->execname, pam->fname, NO_RGHT));
	if ((pam->dst_fd = open(EXEC_NAME, O_CREAT | O_WRONLY, 0755)) < 0)
	{
		printf("Error bblblblbl\n");
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

static void		find_codecave(t_pars pam)
{
	printf("VERIF .TEXT\n");
	printf("offset = %lX to %lX\n", pam.sect.sh_offset, pam.sect.sh_offset + pam.sect.sh_size);
	for (int i = 0; i < pam.sect.sh_size; i++)
	{
		if (i != 0 && i % 16 == 0)
			printf("\n");
		printf("%02X ", *(pam.content + pam.sect.sh_offset + i));
	}
	printf("\n");
}

uint8_t			ascii_to_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
}

static int		find_pattern(const uint8_t *ptr, uint32_t pattern, int size)
{
	int		i;
	int		j;
	uint32_t	*tmp;

	tmp = 0;
	for (i = 0; i < size; i++)
	{
		tmp = (uint32_t*)&ptr[i];
		printf("%08x %08x\n", *tmp, pattern);
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
	uint32_t		vaddr;
	uint32_t		*res;

	res = pam->content + pam->off_gap + POFF + offset;
	vaddr = addr + pam->seg.p_vaddr + pam->off_gap - pam->seg.p_offset;
	printf("change offset %x for %x\n", pam->off_gap + POFF + offset, vaddr);//pam->off_gap + addr);
	*res = vaddr;
	//*(pam->content + pam->off_gap + POFF + offset) = vaddr;//*(pam->content + pam->off_gap + addr);
}

static void		patch_len(t_pars *pam, uint32_t len, int offset)
{
	uint32_t		*res;

	res = pam->content + pam->off_gap + POFF + offset;
	*res = len;
}

static void		patch(t_pars *pam)
{
	int				offset;
	uint8_t			byte = 0;
	EHDR			*temp;
	unsigned int	relative_val;

	temp = (EHDR*)pam->content;
	temp->e_entry = pam->off_gap + pam->seg.p_vaddr - pam->seg.p_offset;
	printf("old entry = %04x -- new = %04x\n", pam->hdr.e_entry, temp->e_entry);
	printf("uwu = %x\n", pam->off_gap + MSIZE);
	relative_val = pam->seg.p_vaddr + pam->seg.p_filesz - pam->hdr.e_entry + MSIZE / 2;
	relative_val = -relative_val;
	relative_val = pam->hdr.e_entry - (pam->seg.p_vaddr + pam->seg.p_filesz + MSIZE / 2 + 5);
	printf("relative val = %d\n", relative_val);
	for (int i = 0; i < MSIZE /*/ 2*/; i++)
	{
		if (pam->content[pam->off_gap + i] == 0xe9)
		{
			printf("jump found\n");
			for (int j = 1; j <= 4; j++)
				printf("%x\n", pam->content[pam->off_gap + i + j]);
			memcpy(pam->content + pam->off_gap + i + 1, &relative_val, sizeof(int));
		}
	}
	if ((offset = find_pattern(pam->content + pam->off_gap + POFF, 0xAAAAAAAA, PSIZE)) < 0)
		printf("0xAAAAAAAA not found\n");
	patch_addr(pam, pam->sect.sh_addr, offset);
	if ((offset = find_pattern(pam->content + pam->off_gap + POFF, 0xBBBBBBBB, PSIZE)) < 0)
		printf("0xBBBBBBBB not found\n");
	patch_len(pam, pam->sect.sh_size, offset);
	if ((offset = find_pattern(pam->content + pam->off_gap + POFF, 0xCCCCCCCC, PSIZE)) < 0)
		printf("0xCCCCCCCC not found\n");
	patch_addr(pam, KOFF, offset);
	if ((offset = find_pattern(pam->content + pam->off_gap + POFF, 0xDDDDDDDD, PSIZE)) < 0)
		printf("0xDDDDDDDD not found\n");
	patch_len(pam, pam->klen, offset);
/*	*(pam->content + pam->off_gap + 41) = 0xe9;
	printf("relative val = %d\n", relative_val);
	memcpy(pam->content + pam->off_gap + 42, &relative_val, sizeof(int));*/
}

static void		encrypt(t_pars *pam)
{
	printf("ENC !! %X of size %X\n", pam->sect.sh_offset, pam->sect.sh_size);
	rc4(pam->content + pam->sect.sh_offset, pam->sect.sh_size, pam->key, pam->klen);
}

int				write_payload(t_pars *pam)
{
	int			j;
	uint8_t		byte = 0;
	const char	*payload = PAYLOAD;

	j = 0;
	printf("fill gap at %d\n", pam->off_gap);
	for (int i = 0; i < sizeof(PAYLOAD); i++)
	{
		byte = byte << 4;
		byte |= ascii_to_hex(payload[i]);
		printf("[%d] = %c -- %02x\n", i, payload[i], byte);
		if (i % 2 == 1)// && i != 0)
		{
			printf("cont[%d] = %02x -- byte = %02x\n", pam->off_gap +j, *(pam->content + pam->off_gap + i), byte);
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
	printf("write %x bytes\n", size);
	for (i = 0; i < size; i++)
	{
		byte = byte << 4;
		byte |= ascii_to_hex(shellcode[i]);
		printf("%c", shellcode[i]);
		if (i % 2 == 1)// && i != 0)
		{
			*(pam->content + offset + j) = byte;
			byte = 0;
			j++;
		}
	}
	printf("\n");
}

int				woody(t_pars pam)
{
	int			len;
	char		buff[BUFFLEN];
	uint8_t		*cipher;
	//const char	isnar[] = "NO ONE CAN SAVE FROM DEATH";

	if (open_file(&pam) < 0)
		return (0);
	if (read_file(&pam) == -1)
		return (0);
	check_elf(&pam);
	find_codecave(pam);
	printf("size = %d\n", sizeof(PAYLOAD));
	if ((len = find_gap(&pam, pam.hdr)) < GSIZE)
	{
		printf("Olympique palaplass\n");
		return (0);
	}
	printf("size gap = %x\n", len);
	printf("write message at %x of size %x to %x\n", pam.off_gap, MSIZE, pam.off_gap + MSIZE);
	write_shellcode(&pam, MESSAGE, sizeof(MESSAGE), pam.off_gap);
	printf("write prep at %x of size %x to %x\n", pam.off_gap + POFF, PSIZE, pam.off_gap + POFF + PSIZE);
	write_shellcode(&pam, PREP, sizeof(PREP), pam.off_gap + POFF);
	printf("write rc4 at %x of size %x to %x\n", pam.off_gap + ROFF, RSIZE, pam.off_gap + ROFF + RSIZE);
	write_shellcode(&pam, RC4, sizeof(RC4), pam.off_gap + ROFF);
	printf("write end at %x of size %x to %x\n", pam.off_gap + EOFF, ESIZE, pam.off_gap + EOFF + ESIZE);
	write_shellcode(&pam, END, sizeof(END), pam.off_gap + EOFF);
	printf("write key at %x of size %x\n", pam.off_gap + KOFF, pam.klen);
	ft_memcpy(pam.content + pam.off_gap + KOFF, pam.key, pam.klen);
	for (int i = 0; i < pam.klen; i++)
		printf("%02x ", pam.key[i]);
	printf("\n");
	//write_payload(&pam);
	//encrypt(&pam);
	patch(&pam);
	//pam.hdr.e_entry = 0;
	write(pam.dst_fd, pam.content, pam.len);
	/*while ((len = read(pam.src_fd, buff, BUFFLEN)) > 0)
	{
		//rc4(isnar, ft_strlen(isnar), pam.key, pam.klen);
		cipher = rc4(buff, len, pam.key, pam.klen);
		printf("len = %d\n", len);
		for (int i = 0; i < len; i++)
			write(pam.dst_fd, &cipher[i], 1);
		//write(pam.dst_fd, cipher, len);
		free(cipher);
	}*/
	return (0);
}
