#include "woody.h"

static int		error_elf(const char *err)
{
	printf("./woody_woodpacker stopped: %s\n", err);
	return (-1);
}

static int		check_magic(EHDR hdr)
{
	printf("%x - %x\n", hdr.e_ident[EI_MAG0], M0);
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

	printf("VERIF SECTION\n-------------------------\n");
	printf("cont add = %p\n", pam->content);
	strtab = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx);
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		shdr = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * i);
		name = (char *)(pam->content + strtab->sh_offset + shdr->sh_name);
		//printf("%lld\n", *(strtab->sh_offset + shdr->sh_name));
		//printf("isok\n");
		printf("section %d(%s) -- type %d -- offset = %x\n", i, name, shdr->sh_type, shdr->sh_offset);
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

	printf("hello verif\n");
	printf("cont add = %p\n", pam->content);
	hdr = (EHDR*)pam->content;
	if (check_magic(*hdr) < 0)
		return (error_elf(MAGC_MSG));
	for (int i = 0; i < EI_NIDENT; i++)
		printf("%02x ", hdr->e_ident[i]);
	printf("\n");
	printf("VERIF HEADER\n-------------------------\n");
	printf("entry = %x\nph = %d\nsh = %d\n", hdr->e_entry, hdr->e_phoff, hdr->e_shoff);
	printf("%d - %d\n", hdr->e_ehsize, sizeof(EHDR));
	if (hdr->e_ehsize != sizeof(EHDR))
		return (error_elf(SIZE_MSG));
	printf("ph --- %d entries of size %d at %x\n", hdr->e_phnum, hdr->e_phentsize, hdr->e_phoff);
	printf("sh --- %d entries of size %d at %x\n", hdr->e_shnum, hdr->e_shentsize, hdr->e_shoff);
	if (hdr->e_ident[EI_CLASS] == ELFCLASS32)
		printf("32 bits object file\n");
	else if (hdr->e_ident[EI_CLASS] == ELFCLASS64)
		printf("64 bits object file\n");
	else
		return (error_elf(HDR_MSG));
	if (hdr->e_ident[EI_DATA] == ELFDATA2LSB)
		printf("little endian\n");
	else if (hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		printf("big endian\n");
	else
		return (error_elf(HDR_MSG));
	printf("%d\n", hdr->e_type);
	if (hdr->e_type != ET_EXEC && hdr->e_type != ET_DYN)
		return (error_elf(TYPE_MSG));
	if ((pars_section(pam, *hdr)) == -1)
		return (-1);
	pam->hdr = *hdr;
	printf("Bye verif\n");
	return (0);
}
