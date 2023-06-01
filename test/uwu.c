typedef struct	s_test
{
	char	f;
	void	(*func)(void *);
}				t_test;

void		ft_putstr(void *ptr)
{
	printf("%s\n", ptr);
}

void		ft_putnbr(void *ptr)
{
	printf("%d\n", atoi(ptr));
}

t_test		array[2] = {{'s', &ft_putstr}, {'d', &ft_putnbr}};

int	get_idx(char c)
{
	for (int i = 0; i < 2; i++)
	{
		if (array[i].f == c)
			return (i);
	}
	return (-1);
}

int main(int argc, char **argv)
{
	int		idx;
	if (argc != 3)
		return 0;
	if ((idx = get_idx(argv[1][0])) != -1)
	{
		array[idx].func(argv[2]);
	}
}
