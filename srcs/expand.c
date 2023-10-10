#include "woody.h"

void		print_hdr(t_pars *pam)
{
	printf("HEADER\n");
	printf("-----------------------------------\n");
	printf("shoff = %ld phoff = %ld\n", pam->hdr.e_shoff, pam->hdr.e_phoff);
}

void			print_seg(t_pars *pam)
{
	EPHR		*phdr;
	EHDR		hdr;

	hdr = pam->hdr;
	printf("SEGMENT\n");
	printf("-----------------------------------\n");
	printf("Base seg offset = %llx\n", pam->seg.p_offset);
	for (int i = 0; i < hdr.e_phnum; i++)
	{
		phdr = (EPHR*)(pam->content + hdr.e_phoff + hdr.e_phentsize * i);
		printf("segment %2d (size %4x) starting at offset %4llx to %4llx -- in memory %4llx\n", i, phdr->p_filesz, phdr->p_offset, phdr->p_offset + phdr->p_filesz, phdr->p_vaddr);
	}
}

void			print_sec(t_pars *pam)
{
	char	*name;
	EHDR	hdr;
	ESHR	*shdr;
	ESHR	*strtab;

	hdr = pam->hdr;
	printf("SECTION\n");
	printf("-----------------------------------\n");
	printf("shoff = %llx\n", pam->hdr.e_shoff);
	strtab = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx);
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		shdr = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * i);
		name = (char *)(pam->content + strtab->sh_offset + shdr->sh_name);
		printf("section %2d (%18s) starting at offset %4llx link %2llx\n", i, name, shdr->sh_offset, shdr->sh_link);
	}

}

#define SEGSZ sizeof(EPHR)

void		expand_rela(t_pars *pam, ESHR *shdr, Elf64_Off off)
{
	unsigned long	size = 0;
	Elf64_Rela		*rela;

	while (size < shdr->sh_size)
	{
		rela = (Elf64_Rela*)(pam->content + shdr->sh_offset + size);
		if (rela->r_addend >= (long)off)
			rela->r_addend += SEGSZ;
		if (rela->r_offset >= off)
		{
			rela->r_offset += SEGSZ;
		}
		size += sizeof(Elf64_Rela);
	}
}

void		expand_sym(t_pars *pam, ESHR *shdr, Elf64_Off off)
{
	unsigned long	size = 0;
	Elf64_Sym		*sym;

	while (size < shdr->sh_size)
	{
		sym = (Elf64_Sym*)(pam->content + shdr->sh_offset + size);
		if (sym->st_value >= off)
			sym->st_value += SEGSZ;
		size += sizeof(Elf64_Sym);
	}
}

void		expand_dyn(t_pars *pam, ESHR *shdr, Elf64_Off off)
{
	unsigned long	size = 0;
	Elf64_Dyn		*dyn;

	while (size < shdr->sh_size)
	{
		dyn = (Elf64_Dyn*)(pam->content + shdr->sh_offset + size);
		if (dyn->d_un.d_val >= off && dyn->d_un.d_val < (unsigned long)pam->len)
			dyn->d_un.d_val += SEGSZ;
		size += sizeof(Elf64_Dyn);
	}
}


uint32_t		expand_segment(t_pars *pam, int off)
{
	EPHR		*phdr;
	EHDR		hdr;

	hdr = pam->hdr;
	for (int i = 0; i < hdr.e_phnum; i++)
	{
		phdr = (EPHR*)(pam->content + hdr.e_phoff + hdr.e_phentsize * i);
		if ((unsigned long)off <= phdr->p_offset)
		{
			phdr->p_offset += SEGSZ;
			phdr->p_vaddr += SEGSZ;
			phdr->p_paddr += SEGSZ;
			memcpy(phdr, pam->content + hdr.e_phoff + hdr.e_phentsize * i, sizeof(EPHR));
		}
		if (phdr->p_type == PT_LOAD)
			phdr->p_flags |= PF_X | PF_W;
		if (phdr->p_offset == 0x40 || phdr->p_offset == 0)
		{
			phdr->p_memsz += SEGSZ;
			phdr->p_filesz += SEGSZ;
		}
	}
	return (0);
}

void		expand_section(t_pars *pam, uint32_t off)
{
	char	*name;
	EHDR	hdr;
	ESHR	*shdr;
	ESHR	*strtab;

	hdr = pam->hdr;
	strtab = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx);
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		shdr = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * i);
		name = (char *)(pam->content + strtab->sh_offset + shdr->sh_name);
		if (strncmp(name, ".rela.", 6) == 0)
			expand_rela(pam, shdr, off);
		if (strcmp(name, ".dynamic") == 0)
			expand_dyn(pam, shdr, off);
		if (strcmp(name, ".symtab") ==  0)
			expand_sym(pam, shdr, off);
		if (shdr->sh_offset >= off)
		{
			shdr->sh_offset += SEGSZ;
			shdr->sh_addr += SEGSZ;
			memcpy(shdr, pam->content + hdr.e_shoff + hdr.e_shentsize * i, sizeof(ESHR));
		}
	}
	pam->hdr.e_shoff += SEGSZ;
	pam->hdr.e_entry += SEGSZ;
}

void		expand(t_pars *pam)
{
	uint32_t	off;
	char		*expanded;

	pam->len += SEGSZ;
	expanded = (char *)malloc(sizeof(char) * pam->len + GSIZE + 18);
	off = pam->hdr.e_phoff + pam->hdr.e_phnum * pam->hdr.e_phentsize;
	expand_segment(pam, off);
	expand_section(pam, off);
	pam->hdr.e_phnum += 1;
	ft_memcpy(expanded, pam->content, off);
	ft_bzero(expanded + off, SEGSZ);
	ft_memcpy(expanded + off + SEGSZ, pam->content + off, pam->len - off);
	free(pam->content);
	pam->content = (uint8_t*)expanded;
	pam->new_seg = creat_segment(pam, off, pam->len);
	pam->off_gap = pam->len;
	pam->memory_offset = 0x1000;
	pam->len += GSIZE + 16;
}
