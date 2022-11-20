#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

uint8_t		*rc4(const char *txt, int len, const char *key, int klen);


int			main(int argc, char **argv)
{
	const char	*key = "THIS IS THE GOOD KEY";
	const char	*txt = "NO ONE CAN SAVE FROM DEATH\n";
	uint8_t		*stab;
	char		*ttab;
	if (argc == 1)
	{
		printf("%s%d, %s, %d\n", txt, strlen(txt), key, strlen(key));
		ttab = rc4(txt, strlen(txt), key, strlen(key));
		for (int i = 0; i < strlen(txt); i++)
			printf("%d\n", stab[i]);
		return (0);
	}
	printf("ALive.1\n");
	int fd;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	printf("ALive.2\n");
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 30);
	int		len;
	printf("1 %p %p\n", txt, buf);
	len = read(fd, buf, 27);
	printf("2 %p %p\n", txt, buf);
	printf("ALive.3\n");
	for (int i = 0; i < len; i++)
		printf("%c", buf[i]);
	printf("ALive.3.1\n");
	printf("%d, %s, %d\n", len, key, strlen(key));
	ttab = rc4(buf, len, key, strlen(key));
	printf("ALive.4\n");
	int fd2;
	if ((fd2 = open("woodyrc4", O_WRONLY | O_CREAT, 0666)) < 0)
		return (0);
	printf("ALive.5\n");
	for (int i = 0; i < len; i++)
		write(fd2, ttab + i, 1);
	printf("ALive.6\n");
	return (0);
}
