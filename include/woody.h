#ifndef WOODY_H
# define WOODY_H

# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

# include <elf.h>

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# define NO_ARG 0
# define NO_RGHT 1
# define WG_FLAG 2
# define WG_ARCH 3
# define F_OTHER 4

# define NB_ERR 5

# define KEY_DSIZE 8
# define KEY_MSIZE 46

# define BUFFLEN 2048

# define EXEC_NAME "woody"
# define ENCR_SECT ".text"

# define M0 0x7f
# define M1 0x45
# define M2 0x4c
# define M3 0x46

# define EHDR Elf64_Ehdr
# define ESHR Elf64_Shdr
# define EPHR Elf64_Phdr

# define MAGC_ERR -1
# define READ_ERR -2
# define SIZE_ERR -3
# define HDR_ERR -4

//# define PAYLOAD "52       b801000000bb010000006a0a682e2e2e2e684459000068574f4f00682e2e2e2e4889e6ba210000000f055858585858 5a       6860100000c3"
//# define PAYLOAD "5250535651b801000000bb010000006a0a682e2e2e2e684459000068574f4f00682e2e2e2e4889e6ba210000000f055858585858595e5b585a6860100000c3"
//# define PAYLOAD "eb1e5e4831c0b0014889c74889fa4883c20e0f054831c04883c03c4831ff0f05e8ddffffff2e2e2e2e574f4f44592e2e2e2e0a"

# define MESSAGE "52eb185e4831c0b0014889c74889fa4883c20d0f055ae9a6aaaaaae8e3ffffff2e2e2e2e574f4f44592e2e2e2e0a"
# define MSIZE 46

# define PREP "57565251bfaaaaaaaabebbbbbbbbbaccccccccb9dddddddd"
# define PSIZE 24
# define POFF MSIZE//sizeof(MESSAGE) / 2

# define RC4 "5357564989d04989c9bb0001000031c9eb2556575152415041514889f7e80000000085c0415941585a595f5e0f84fb0000004989c331c9666789890000000031d24889c849f7f1418a04106788810000000048ffc14839d97cdd31c94d31d24d31c04d31c9678a8100000000678a91000000004989c04989d14d01c24d01ca31d24c89d048f7f34989d24831c04831d2678a9100000000418a8200000000678881000000004188920000000048ffc14839d97cb131c94d31c04d31c949ffc031d24c89c048f7f34989d0418a90000000004901d131d24c89c848f7f34989d131c031d2418a9000000000418a810000000041888000000000418891000000004989d24901c24831d24c89d048f7f34989d231d2418a92000000006732140f4889f88814089048ffc14839f17c8f5e5f5bc3"
# define RSIZE 305
# define ROFF POFF + PSIZE

# define END "595a5e5fe9a6aaaaaa"
# define ESIZE 9
# define EOFF ROFF + RSIZE//sizeof(RC4) / 2

# define KOFF EOFF + ESIZE

# define PAYLOAD "52eb185e4831c0b0014889c74889fa4883c20d0f055ae9a6aaaaaae8e3ffffff2e2e2e2e574f4f44592e2e2e2e0a"
//# define PSIZE 46

# define GSIZE MSIZE + PSIZE + RSIZE + ESIZE

//LAST TEST SUR WOODY
//# define PAYLOAD "52eb135e4831c0b0014889c74889fa4883c20d0f055ae8e8ffffff2e2e2e2e574f4f44592e2e2e2e0a"

//CEUX LA MARCHE HELLO 
//# define PAYLOAD "52eb185e4831c0b0014889c74889fa4883c20d0f055ae99fa5ffffe8e3ffffff2e2e2e2e574f4f44592e2e2e2e0a"

//# define PAYLOAD "52eb185e4831c0b0014889c74889fa4883c20d0f055ae95ffeffffe8e3ffffff2e2e2e2e574f4f44592e2e2e2e0a"

//PREMIER QUI MARCHE + ou - 
//# define PAYLOAD "52eb185e4831c0b0014889c74889fa4883c20d0f055a6800001060e8e3ffffff2e2e2e2e574f4f44592e2e2e2e0a"


# define MAGC_MSG "wrong magic number"
# define READ_MSG "an error occured while reading file"
# define SIZE_MSG "header size incorrect"
# define HDR_MSG "header might be corrupted"
# define TYPE_MSG "wrong type"

typedef struct		s_pars
{
	char			*execname;			//name of exec (must be woody)
	char			*fname;				//name of binary to encryt
	uint8_t			*content;			//his content
	int				len;				//his len
	uint8_t			*key;				//the key used for encrytion
	int				klen;				//len of the key
	int				src_fd;				//fd of the input binary
	int				dst_fd;				//fd of the output binary
	EHDR			hdr;
	EPHR			seg;
	ESHR			sect;			//index of the section to encrypt (must be .text)
	int				off_gap;
}					t_pars;

/*
 *code_cave.c
*/
int		find_gap(t_pars *pam, EHDR hdr);

/*
 *	elf.c
*/
int		check_elf(t_pars *pam);

/*
 *	error_input.c
*/
int			error_input(char *name, char *input, int err);

/*
 *	parser.c
*/
int			parser(t_pars *pam, char **arg, int n);

/*
 *	rc4.c
*/
uint8_t		*rc4(const char *plain, int plain_len, uint8_t *key, int klen);

/*
 *	woody.c
*/
int			woody(t_pars pam);
#endif
