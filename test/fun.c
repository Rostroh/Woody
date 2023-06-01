#include <stdio.h>

int		a(char *str)
{
	printf("str dans a %s\n", str);
}

int		b(char *str)
{
	printf("str dans b %s\n", str);
}

int		main(void)
{
	char	*str = "salut, on est fun";

	printf("str dans main %s\n", str);
	a(str);
	b(str);
	return (0);
}
