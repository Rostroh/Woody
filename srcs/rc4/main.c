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
	int			fd;
	char		*s1;
	const char	*key = "THIS IS THE GOOD KEY";

	if (argc == 1)
	{
		printf("no arg\n");
		return (0);
	}
	s1 = malloc(50);
	fd = open(argv[1], O_RDONLY);
	read(fd, s1, 50);
	printf("%s\n", s1);
	rc4(s1, 27, key, strlen(key));
	printf("%s\n", s1);
	return (0);
}
