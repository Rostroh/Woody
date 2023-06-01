#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t		*rc4(const char *txt, int len, const char *key, int klen);

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("no arg\n");
		return (0);
	}
	int		fd_in = open(argv[1], O_RDONLY);
	int		fd_out = open(argv[2], O_CREAT | O_WRONLY, 0755);

	int		len = lseek(fd_in, 0, SEEK_END);
	lseek(fd_in, 0, SEEK_SET);

	char	*content;
	if (!(content = malloc(sizeof(char) * len)))
	{
		printf("Error malloc\n");
		return (0);
	}

	int		off = 0;
	int		rd = 0;
	while ((rd = read(fd_in, content + off, 512)) > 0)
		off += rd;

	uint8_t		key[4];

	key[0] = 0xde;
	key[1] = 0xad;
	key[2] = 0xbe;
	key[3] = 0xef;
	printf("content (%p) created (len %x)\n", content, len);
	rc4(content, len, key, 4);
	printf("content cypher\n");
	write(fd_out, content, len);
	close(fd_in);
	close(fd_out);
	return (0);
}
