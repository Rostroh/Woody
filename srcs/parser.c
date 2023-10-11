#include "woody.h"

static uint8_t		*creat_key(void)
{
	int		len;
	int		randfd;
	uint8_t	*key;

	key = (uint8_t *)malloc(sizeof(uint8_t) * KEY_DSIZE);
	if ((randfd = open("/dev/urandom", O_RDONLY)) <= 0)
		return (NULL);
	if ((len = read(randfd, key, KEY_DSIZE)) < KEY_DSIZE)
		return (NULL);
	return (key);
}

static uint8_t			ascii_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0xff);
}

//Read hexadecimal key from arg -- "FFAA" gives key == 0xFFAA
static int				read_key(t_pars *pam, uint8_t *key)
{
	int			off;
	int			j;
	uint8_t		mask;
	uint32_t	res;

	off = 0;
	if (ft_strncmp((char*)key, "0x", 2) == 0)
		off = 2;
	if ((pam->klen = ((ft_strlen((char*)key)) - off) / 2) > KEY_MSIZE)
		return (error_input(pam->execname, "Provided key is too long", F_OTHER));
	j = 0;
	mask = 0;
	pam->key = (uint8_t *)malloc(sizeof(uint8_t) * pam->klen);
	for (int i = 0; (size_t)(i + off) < ft_strlen((char*)key); i++)
	{
		res = ascii_val(key[i + off]);
		if (res == 0xff)
			return (error_input(pam->execname, "Provided key contains non-hexadecimal values", F_OTHER));
		pam->key[j] = pam->key[j] << mask | res;
		if (i != 0 && i % 2 == 1)
		{
			j++;
			mask = 0;
		}
		else
			mask = 4;
	}
	return (0);
}

//Read characters key from arg amd convert it in hexadecimal -- "Hello" gives key == 
static int		read_kkey(t_pars *pam, char *key)
{
	if ((pam->klen = ft_strlen(key)) > KEY_MSIZE)
		return (error_input(pam->execname, "Provided key is too long (max 256 bytes)", F_OTHER));
	pam->key = (uint8_t *)malloc(sizeof(uint8_t) * pam->klen);
	for (int i = 0; i < pam->klen; i++)
		pam->key[i] = key[i];
	return (0);
}

int				parser(t_pars *pam, char **arg, int n)
{
	char	opt;
	bool	kf = false;

	while ((opt = ft_getopt(n, arg, "k:K:")) != -1)
	{
		switch (opt)
		{
			case 'k':
			{
				kf = true;
				if (read_key(pam, (unsigned char*)optarg) == -1)
					return (-1);
				break;
			}
			case 'K':
			{
				kf = true;
				if (read_kkey(pam, optarg) == -1)
					return (-1);
				break ;
			}
			default:
				return (-1);
		}
	}
	if (!kf)
	{
		if (!(pam->key = creat_key()))
			return (error_input(pam->execname, "An error occured while generating key", F_OTHER));
		pam->klen = KEY_DSIZE;
	}
	return (0);
}
