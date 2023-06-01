#include <stdio.h>

void		*asmalloc(int nb);

int		main(void)
{
	int		i;
	char	*str = asmalloc(20);
	
	printf("%c\n", str[0]);
	return (0);
}
