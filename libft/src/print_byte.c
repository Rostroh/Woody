#include "libft.h"

void			print_byte(unsigned char c)
{
	int		and = 128;
	int		shift = 7;

	for (int i = 0; i < 8; i++)
	{
		ft_printf("%d", (c & and) >> shift);
		and = and >> 1;
		shift--;
	}
	ft_putstr(" ");
}

void			print_u16(uint16_t var)
{
	uint8_t		res;

	for (int i = 1; i >= 0; i--)
	{
		res = (var & (0xFF << i * 8)) >> 8 * i;
		print_byte(res);
	}
}

void			print_u32(uint32_t var)
{
	uint8_t		res;

	for (int i = 3; i >= 0; i--)
	{
		res = (var & (0xFF << i * 8)) >> 8 * i;
		print_byte(res);
	}
}

void			print_u64(uint64_t var)
{
	uint8_t		res;

	for (int i = 7; i >= 0; i--)
	{
		res = (var & (0xFF << i * 8)) >> 8 * i;
		print_byte(res);
	}
}
