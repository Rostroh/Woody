#include "libft.h"

int			optind = 1;
char		*optarg = 0;
static int	nextchar = 1;

static int			check_option(const char *pattern)
{
	int			i;

	i = 0;
	if (!pattern[i])
		ft_printf("wtf\n");
	while (pattern[i])
	{
		if (pattern[i] != ':')
			break ;
		i++;
	}
	return (i);
}

static int			find_opt(char c, const char *check, int *option)
{
	int		i;

	i = 0;
	while (check[i])
	{
		if (c == check[i])
		{
			*option = check_option(check + i + 1);
			return (i);
		}
		i++;
	}
	return (-1);
}

int			ft_getopt(int argc, char *argv[], const char *optstring)
{
	char	c;
	int		idx;
	int		option;

//	printf("option = %s\n", argv[optind]);
	if (optind >= argc || argv[optind][0] != '-')
		return (-1);
	option = 0;
	idx = find_opt(argv[optind][nextchar], optstring, &option);
	if (idx == -1)
	{
		ft_printf("%s: invalid option -- '%c'\n", argv[0], argv[optind][nextchar]);
		c = '?';
	}
	else
		c = optstring[idx];
	if (option != 0)
	{
		if (nextchar < (int)ft_strlen(argv[optind]) - 1)
			optarg = argv[optind] + nextchar + 1;
		else if (optind < argc - 1 && option == 1)
		{
			optind++;
			optarg = argv[optind];
		}
		else if (option == 1)
		{
			ft_printf("%s: option requires an argument -- '%c'\n", argv[0], c);
			c = '?';
		}
	}
	if (nextchar < (int)ft_strlen(argv[optind]) - 1 && option == 0)
		nextchar++;
	else
	{
		optind++;
		nextchar = 1;
	}
	return (c);
}
