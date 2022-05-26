#include "libft.h"
#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>
#define BASESET_DEC "0123456789"

// int	ft_strncmp(const char *str1, const char *str2, size_t len)
// {
// 	int		diff;
// 	size_t	i;

// 	i = 0;
// 	while (1)
// 	{
// 		diff = (unsigned char)str1[i] - (unsigned char)str2[i];
// 		if (diff != 0 || str1[i] == '\0' || ++i == len)
// 			return (diff);
// 	}
// }

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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	convert_int(char **str, t_convspec *cs, int d)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				flag_zero;
	unsigned int	n;
	unsigned int	m;
	int				nlen;
	unsigned int	magnitude;
	int				len;
	int				i;
	int				j;
	char			*baseset;

	if (d < 0)
		n = -d;
	else
		n = d;
	nlen = 0;
	if (!(n == 0 && cs->flag_period && cs->precision == 0))
	{
		m = n;
		while(1)
		{
			nlen++;
			m /= 10;
			if (m == 0)
				break ;
		}
		magnitude = upow(10, nlen - 1);
	}
	leading_zeros = 0;
	if (cs->flag_period && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	padding_left = 0;
	if (d < 0 || cs->flag_plus)
		nlen++;
	else if (cs->flag_space)
		padding_left++;
	flag_zero = 0;
	if (cs->flag_zero
		&& !cs->flag_period
		&& !cs->flag_minus
		&& cs->field_width > nlen)
	{
		flag_zero = 1;
		leading_zeros = cs->field_width - nlen - padding_left;
	}
	nlen += leading_zeros;
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
		if (d < 0)
			(*str)[i++] = '-';
		else if (cs->flag_plus)
			(*str)[i++] = '+';
		j = 0;
		while (j < leading_zeros)
			(*str)[i + j++] = '0';
		i += j;
		if (nlen > 0)
		{
			m = n;
			baseset = BASESET_DEC;
			while (1)
			{	
				(*str)[i++] = baseset[m / magnitude];
				m %= magnitude;
				magnitude /= 10;
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
