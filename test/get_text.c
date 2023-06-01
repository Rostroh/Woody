#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <elf.h>
#include <string.h>

void		get_text_content(Elf64_Ehdr hdr, char *content, int fd)
{
	char		*name;
	Elf64_Shdr		shdr;
	Elf64_Shdr		strtab;

	memcpy(&strtab, content + hdr.e_shoff + hdr.e_shentsize * hdr.e_shstrndx, sizeof(Elf64_Shdr));
	for (int i = 0; i < hdr.e_shnum; i++)
	{
		memcpy(&shdr, content + hdr.e_shoff + hdr.e_shentsize * i, sizeof(Elf64_Shdr));
		name = content + strtab.sh_offset + shdr.sh_name;
		if (strcmp(name, ".text") == 0)
		{
			printf("write %x bytes in file\n", shdr.sh_size);
			write(fd, content + shdr.sh_offset, shdr.sh_size);
		}
	}
}

int			main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("No args\n");
		return (0);
	}
	int		fd1 = open(argv[1], O_RDONLY);
	int		fd2 = open("plain", O_CREAT | O_WRONLY, 0755);

	int		len = lseek(fd1, 0, SEEK_END);
	char	*content = malloc(sizeof(char) * len);
	lseek(fd1, 0, SEEK_SET);

	int		off = 0;
	int		rd = 0;
	while ((rd = read(fd1, content + off, 512)) > 0)
		off += rd;

	Elf64_Ehdr	hdr;

	memcpy(&hdr, content, sizeof(Elf64_Ehdr));
	get_text_content(hdr, content, fd2);
	close(fd1);
	close(fd2);
	return (0);
}
