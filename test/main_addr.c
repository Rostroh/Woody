#include <stdio.h>

int		main(void)
{
	void	*ptr;

	ptr = &main;
	printf("Hello world\n");
	printf("%p\n", ptr);
	return (0);
}
