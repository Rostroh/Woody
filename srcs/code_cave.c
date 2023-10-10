#include "woody.h"

/*
 * find gap function
 * return the size of the gap in case of sucess, return 0 otherwise
*/
int			off_next_sect(t_pars *pam, EHDR hdr, EPHR *phdr)
{
	EPHR	*actual;
	EPHR	*closest = NULL;

	for (int i = 0; i < hdr.e_phnum; i++)
	{
		actual = (EPHR*)(pam->content + hdr.e_phoff + hdr.e_phentsize * i);
		if (actual->p_offset > phdr->p_offset)
		{
			if (!closest || actual->p_offset < closest->p_offset)
				closest = actual;
		}
	}
	return (closest->p_offset - (phdr->p_offset + phdr->p_filesz));
}

int			section_sz(t_pars *pam)
{
	char	*name;
	EHDR	hdr;
	ESHR	*shdr;
	ESHR	*tmp;
	ESHR	*strtab;

	tmp = &pam->sect;
	hdr = pam->hdr;
	strtab = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx);
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		shdr = (ESHR*)(pam->content + hdr.e_shoff + hdr.e_shentsize * i);
		name = (char *)(pam->content + strtab->sh_offset + shdr->sh_name);
		if (ft_strcmp(name, ".fini") == 0)
		{
			shdr->sh_size += GSIZE + 0x1f;
			//TODO: jiicheichdsihcosdihceosihceisoc
			//verif si sect in se
			return (shdr->sh_addr + shdr->sh_size - pam->seg.p_offset);
			//return (0);
		//	pam->seg.p_memsz = shdr->sh_addr + shdr->sh_size - pam->seg.p_offset;
		//	pam->seg.p_filesz = shdr->sh_addr + shdr->sh_size - pam->seg.p_offset;
		}
	}
	return (-1);
}

int			find_gap(t_pars *pam, EHDR hdr)
{
	int		size_gap;
	EPHR	*phdr;
	int		end_seg;
	int		closest_start;

	size_gap = 0;
	end_seg = 0;
	closest_start = 0;
	pam->new_seg = NULL;
	for (int i = 0; i < hdr.e_phnum; i++)
	{
		phdr = (EPHR*)(pam->content + hdr.e_phoff + hdr.e_phentsize * i);
		if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X))
		{
			pam->seg = *phdr;
			end_seg = phdr->p_offset + phdr->p_filesz;
			if ((size_gap = off_next_sect(pam, hdr, phdr)) >= GSIZE)
			{
				//section_sz(pam);
				phdr->p_memsz = section_sz(pam);
				while (phdr->p_memsz % 8 != 0)
					phdr->p_memsz++;
				phdr->p_filesz = phdr->p_memsz;
				//phdr->p_memsz += GSIZE;
				//phdr->p_filesz += GSIZE;
			}
			pam->off_gap = end_seg + 1;
			phdr->p_flags += PF_W;
			return (size_gap);
		}
		else if (end_seg)
		{
			if (!closest_start || (pam->seg.p_offset < phdr->p_offset && closest_start > phdr->p_offset))
				closest_start = phdr->p_offset;
		}
	}
	if (end_seg && closest_start)
	{
		size_gap = closest_start - end_seg;
		pam->off_gap = end_seg + 1;
	}
	else
		printf("Gap error raised\n");
	return (size_gap);
}
