#include "woody.h"

static void		msg_noarg(char *name, char *input)
{
	ft_printf("Usage %s:\n%s [-k key] binary\n", name, name, input);
}

static void		msg_noright(char *name, char *input)
{
	ft_printf("Error %s: Can't open file %s\n", name, input);
}

static void		msg_wrongflg(char *name, char *input)
{
	ft_printf("Error %s: invalid option %s\nList of valid flags:\n-k\n", name, input);
}

static void		msg_other(char *name, char *input)
{
	printf("Error %s: %s\n", name, input);
}

int				error_input(char *name, char *input, int err)
{
	static void		(*error_msg[NB_ERR])(char *name, char *input) = {&msg_noarg, &msg_noright, &msg_wrongflg, &msg_other};

	error_msg[err](name, input);
	return (-1);
}
