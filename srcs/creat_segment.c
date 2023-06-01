#include "woody.h"

EPHR		*creat_segment(t_pars *pam, int file_off, int offset)
{
	EPHR	*phdr;

	phdr = (EPHR*)(pam->content + file_off);
	phdr->p_type = PT_LOAD;
	phdr->p_flags = PF_X | PF_R | PF_W;
	phdr->p_offset = offset;
	phdr->p_vaddr = 0x1000 + offset;
	phdr->p_paddr = phdr->p_vaddr;
	phdr->p_filesz = GSIZE;
	phdr->p_memsz = GSIZE;
	phdr->p_align = 4;
	return (phdr);
}
