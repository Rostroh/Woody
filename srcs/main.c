#include "woody.h"

static void		print_key(unsigned char *key, int klen)
{
	printf("Key : 0x");
	for (int i = 0; i < klen; i++)
		printf("%02X", key[i]);
	printf("\n");
}

int				main(int ac, char **av)
{
	t_pars		param;
	
	if (ac == 1)
		return (error_input(av[0], NULL, NO_ARG));
	ft_bzero(&param, sizeof(param));
	param.execname = av[0];
	if (parser(&param, av, ac) == -1)
		return (-1);
	if (optind >= ac)
		return (error_input(av[0], "No file specified", F_OTHER));
	param.memory_offset = 0;
	param.fname = av[optind];
	if (woody(param) == 0)
		print_key(param.key, param.klen);
	return (0);
}
