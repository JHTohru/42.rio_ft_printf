#include "libft.h"
#include "conversion.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")
#define BASESET_HEXU (BASESET_DEC "ABCDEF")

uintptr_t	ptrpow(uintptr_t b, uintptr_t e)
{
	uintptr_t	n;

	n = 1;
	while (e > 0)
	{
		n *= b;
		e--;
	}
	return (n);
}

int	convert_ptr(char **str, t_convspec *cs, void *p)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				nlen;
	uintptr_t		n;
	uintptr_t		magnitude;
	int				len;
	int				i;
	int				j;
	char			*baseset;
	char			*prefix;
	int				prefix_len;

	nlen = 0;
	if (!(p ==(void *) 0 && cs->flag_period && cs->precision == 0))
	{
		n = (uintptr_t)p;
		while(1)
		{
			nlen++;
			n /= 16;
			if (n == 0)
				break ;
		}
		magnitude = ptrpow(16, nlen - 1);
	}
	leading_zeros = 0;
	if (cs->flag_period && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	nlen += leading_zeros;
	prefix = "0x";
	prefix_len = (int)ft_strlen(prefix);
	padding_left = 0;
	padding_right = 0;
	if (cs->field_width > nlen + prefix_len)
	{
		if (cs->flag_minus)
			padding_right = cs->field_width - nlen - prefix_len;
		else
			padding_left += cs->field_width - nlen - prefix_len;
	}
	len = padding_left + prefix_len + nlen + padding_right;
	*str = malloc((len + 1) * sizeof(char));
	if (*str != NULL)
	{
		i = 0;
		while (i < padding_left)
			(*str)[i++] = ' ';
		(*str)[i++] = '0';
		(*str)[i++] = 'x';
		j = 0;
		while (j < leading_zeros)
			(*str)[i + j++] = '0';
		i += j;
		if (nlen > 0)
		{
			baseset = BASESET_HEXL;
			n = (uintptr_t)p;
			while (1)
			{
				(*str)[i++] = baseset[n / magnitude];
				n %= magnitude;
				magnitude /= 16;
				if (magnitude == 0)
					break ;
			}
		}
		j = 0;
		while (j < padding_right)
			(*str)[i + j++] = ' ';
		(*str)[i + j] = '\0';
		if (i + j != len)
			ft_putendl_fd("OH NO!\n", 2);
	}
	return (len);
}
