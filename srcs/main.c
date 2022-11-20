#include "woody.h"

static void		print_key(unsigned char *key, int klen)
{
	//printf("0x");
	for (int i = 0; i < klen; i++)
		printf("%d ", key[i]);
	printf("\n");
}

int				main(int ac, char **av)
{
	t_pars		param;
	const char	teststr[] = "The quick brown fox jumps over the lazy dog.";
	const char	a[] = "A";
	
	if (ac == 1)
		return (error_input(av[0], NULL, NO_ARG));
	ft_bzero(&param, sizeof(param));
	param.execname = av[0];
	if (parser(&param, av, ac) == -1)
		return (-1);
	if (optind >= ac)
		return (error_input(av[0], "No file specified", F_OTHER));
	param.fname = av[optind];
	woody(param);
	//printf("File = %s\n", param.fname);//Key = 0x%016lX\n", param.fname, param.key);
	print_key(param.key, param.klen);
	//rc4(isnar, ft_strlen(isnar), param.key, param.klen);
	return (0);
}
