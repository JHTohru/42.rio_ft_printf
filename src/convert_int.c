#include "libft.h"
#include "conversion.h"
#include <stdlib.h>
#define BASESET_DEC "0123456789"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

unsigned int	digitslen(unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (1)
	{
		len++;
		n /= 10;
		if (n == 0)
			return (len);
	}
}

int	write_padding(char *str, unsigned int n)
{
	ft_memset((void *)str, ' ', n);
	return (n);
}

int	write_zeros(char *str, unsigned int n)
{
	ft_memset((void *)str, '0', n);
	return (n);
}

int	ft_log(int n, int b)
{
	int	log;

	log = 0;
	while (n > b)
	{
		n /= b;
		log++;
	}
	return(log);
}

int	ft_pow(int b, unsigned int e)
{
	int	n;

	n = 1;
	while (e != 0)
	{
		n *= b;
		e--;
	}
	return (n);
}

unsigned int	ft_mag(int n, int b)
{
	return (ft_pow(b, ft_log(n, b)));
}

int	write_nbr(char *str, int n, char *baseset)
{
	unsigned int	rad;
	unsigned int	mag;
	unsigned int	i;

	i = 0;
	rad = (unsigned int)ft_strlen(baseset);
	mag = ft_mag(n, rad);
	while (1)
	{
		str[i++] = baseset[n / mag];
		n %= mag;
		mag /= rad;
		if (mag == 0)
			break ;
	}
	return (i);
}

int	convert_int(char **str, t_convspec *cs, int d)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				flag_zero;
	unsigned int	n;
	int				nlen;
	int				len;

	n = ft_abs(d);
	if (n != 0 || !cs->flag_period || cs->precision > 0)
		nlen = digitslen(n);
	else
		nlen = 0;
	leading_zeros = 0;
	if (cs->flag_period && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	padding_left = 0;
	if (d < 0 || cs->flag_plus)
		nlen++;
	else if (cs->flag_space)
		padding_left++;
	flag_zero = cs->flag_zero && !cs->flag_period && !cs->flag_minus
		&& cs->field_width > nlen;
	if (flag_zero)
		leading_zeros = cs->field_width - nlen - padding_left;
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
		len = write_padding(*str, padding_left);
		if (d < 0)
			(*str)[len++] = '-';
		else if (cs->flag_plus)
			(*str)[len++] = '+';
		len += write_zeros(*str + len, leading_zeros);
		if (nlen > 0)
			len += write_nbr(*str + len, n, BASESET_DEC);
		len += write_padding(*str + len, padding_right);
		(*str)[len] = '\0';
	}
	return (len);
}
