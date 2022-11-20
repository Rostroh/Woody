#include "woody.h"

/*
 * find gap function
 * return the size of the gap in case of sucess, return 0 otherwise
*/
int			find_gap(t_pars *pam, EHDR hdr)
{
	int		size_gap;
	EPHR	*phdr;
	//EPHR	*seg;
	int		end_seg;
	int		closest_start;

	size_gap = 0;
	end_seg = 0;
	closest_start = 0;
	printf("VERIF SEGMENT\n");
	printf("----------------------------\n");
	printf("cont add = %p\n", pam->content);
	for (int i = 0; i < hdr.e_phnum; i++)
	{
		phdr = (EPHR*)(pam->content + hdr.e_phoff + hdr.e_phentsize * i);
		printf("SEG %d : starts at %lx ends at %lx\n", i, phdr->p_offset, phdr->p_offset + phdr->p_filesz);
		if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X))
		{
			pam->seg = *phdr;
			printf("Is loadable\n");
			end_seg = phdr->p_offset + phdr->p_filesz;
			phdr->p_memsz += GSIZE;//sizeof(PAYLOAD) / 2 + 1;
			phdr->p_filesz += GSIZE;
		}
		else if (end_seg)
		{
			if (!closest_start || (pam->seg.p_offset < phdr->p_offset && closest_start > phdr->p_offset))
			{
				printf("Is kinda close\n");
				closest_start = phdr->p_offset;
			}
		}
	}
	if (end_seg && closest_start)
	{
		printf("Cool\n");
		size_gap = closest_start - end_seg;
		pam->off_gap = end_seg + 1;
	}
	else
		printf("pas cool\n");
	return (size_gap);
}
