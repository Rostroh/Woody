#include "woody.h"

static int		error_elf(const char *err)
{
	printf("./woody_woodpacker stopped: %s\n", err);
	return (-1);
}

static int		check_magic(EHDR hdr)
{
	if (hdr.e_ident[EI_MAG0] != M0)
		return (-1);
	if (hdr.e_ident[EI_MAG1] != M1)
		return (-1);
	if (hdr.e_ident[EI_MAG2] != M2)
		return (-1);
	if (hdr.e_ident[EI_MAG3] != M3)
		return (-1);
	return (0);
}

static int		pars_section(t_pars *pam, EHDR hdr)
{
	ESHR	*shdr;
	ESHR	*strtab;
	char	*name;

	strtab = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx);
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		shdr = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * i);
		name = (char *)(pam->content + strtab->sh_offset + shdr->sh_name);
		if (ft_strncmp(name, ENCR_SECT, ft_strlen(ENCR_SECT)) == 0)
		{
			pam->sect = *shdr;
			return (1);
		}
	}
	printf("Section %s not found\n", ENCR_SECT);
	bzero(shdr, sizeof(ESHR));
	return (-1);
}

int				check_elf(t_pars *pam)
{
	EHDR	*hdr;

	hdr = (EHDR*)pam->content;
	if (check_magic(*hdr) < 0)
		return (error_elf(MAGC_MSG));
	if (hdr->e_ehsize != sizeof(EHDR))
		return (error_elf(SIZE_MSG));
	if (hdr->e_ident[EI_CLASS] == ELFCLASS32)
		;//printf("32 bits object file\n");
	else if (hdr->e_ident[EI_CLASS] == ELFCLASS64)
		;//printf("64 bits object file\n");
	else
		return (error_elf(HDR_MSG));
	if (hdr->e_ident[EI_DATA] == ELFDATA2LSB)
		;//printf("little endian\n");
	else if (hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		;//printf("big endian\n");
	else
		return (error_elf(HDR_MSG));
	if (hdr->e_type != ET_EXEC && hdr->e_type != ET_DYN)
		return (error_elf(TYPE_MSG));
	if ((pars_section(pam, *hdr)) == -1)
		return (-1);
	pam->hdr = *hdr;
	return (0);
}
