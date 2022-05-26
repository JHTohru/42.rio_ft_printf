#include "libft.h"
#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>
#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")
#define BASESET_HEXU (BASESET_DEC "ABCDEF")

unsigned int	upow(unsigned int b, unsigned int e)
{
	int	n;

	n = 1;
	while (e > 0)
	{
		n *= b;
		e--;
	}
	return (n);
}

int	convert_uint(char **str, t_convspec *cs, unsigned int n)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				flag_zero;
	unsigned int	m;
	int				nlen;
	unsigned int	magnitude;
	int				len;
	int				i;
	int				j;
	char			*baseset;
	unsigned int	raddix;

	nlen = 0;
	if (cs->specifier == 'x' || cs->specifier == 'X')
		raddix = 16;
	else
		raddix = 10;
	if (!(n == 0 && cs->flag_period && cs->precision == 0))
	{
		m = n;
		while(1)
		{
			nlen++;
			m /= raddix;
			if (m == 0)
				break ;
		}
		magnitude = upow(raddix, nlen - 1);
	}
	leading_zeros = 0;
	if (cs->flag_period && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	if ((cs->specifier == 'x' || cs->specifier == 'X') && cs->flag_hash)
		nlen += 2;
	flag_zero = 0;
	if (cs->flag_zero
		&& !cs->flag_period
		&& !cs->flag_minus
		&& cs->field_width > nlen)
	{
		flag_zero = 1;
		leading_zeros = cs->field_width - nlen;
	}
	nlen += leading_zeros;
	padding_left = 0;
	padding_right = 0;
	if (cs->field_width > nlen)
	{
		if (cs->flag_minus)
			padding_right = cs->field_width - nlen;
		else if (!flag_zero)
			padding_left += cs->field_width - nlen;
	}
	len = padding_left + nlen + padding_right;
	*str = malloc((len + 1) * sizeof(char));
	if (*str != NULL)
	{	
		i = 0;
		while (i < padding_left)
			(*str)[i++] = ' ';
		if ((cs->specifier == 'x' || cs->specifier == 'X') && cs->flag_hash)
		{
			(*str)[i++] = '0';
			(*str)[i++] = cs->specifier;
		}
		j = 0;
		while (j < leading_zeros)
			(*str)[i + j++] = '0';
		i += j;
		if (nlen > 0)
		{
			if (cs->specifier == 'x')
				baseset = BASESET_HEXL;
			else if (cs->specifier == 'X')
				baseset = BASESET_HEXU;
			else // cs->specifier == 'u'
				baseset = BASESET_DEC;
			m = n;
			while (1)
			{
				(*str)[i++] = baseset[m / magnitude];
				m %= magnitude;
				magnitude /= raddix;
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
