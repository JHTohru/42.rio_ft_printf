#include "libft.h"
#include "conversion.h"
#include <stdint.h>
#include <stdlib.h>
#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")

int	ptr_digits_cnt(void *p, int r)
{
	uintptr_t	n;
	int			cnt;

	n = (uintptr_t)p;
	cnt = 0;
	while (1)
	{
		cnt++;
		n /= (uintptr_t)r;
		if (n == 0)
			return (cnt);
	}
}

int	ptr_conv_len(t_convspec *cs, void *p)
{
	int	len;

	if (p == NULL && cs->flag_period && cs->precision == 0)
		len = 0;
	else
		len = ptr_digits_cnt(p, 16);
	if (cs->flag_period && cs->precision > (unsigned int)len)
		len = cs->precision;
	return (len + 2);
}

uintptr_t	uptr_pow(uintptr_t b, unsigned int e)
{
	uintptr_t	p;

	p = 1;
	while (e != 0)
	{
		p *= b;
		e--;
	}
	return (p);
}

unsigned int	uptr_log(uintptr_t n, unsigned int b)
{
	unsigned int	lg;

	lg = 0;
	while (n > b)
	{
		n /= b;
		lg++;
	}
	return (lg);
}

int	write_ptr(char *str, void *p, char *baseset)
{
	uintptr_t		n;
	uintptr_t		mag;
	unsigned int	rad;
	int				i;

	i = 0;
	rad = (unsigned int)ft_strlen(baseset);
	n = (uintptr_t)p;
	mag = uptr_pow(rad, uptr_log(n, rad));
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

int	write_ptr_conv(char *str, t_convspec *cs, void *p)
{
	int	len;
	int	i;

	i = 0;
	str[i++] = '0';
	str[i++] = 'x';
	len = ptr_conv_len(cs, p);
	if (p != NULL || !cs->flag_period || cs->precision != 0)
	{
		if (cs->flag_period && cs->precision > (unsigned int)len)
			i += write_chars(str + i, '0', cs->precision - len);
		i += write_ptr(str, p, BASESET_HEXL);
	}
	return (i);
}

int	convert_ptr(char **str, t_convspec *cs, void *p)
{
	int	nlen;
	int	i;

	nlen = ptr_conv_len(cs, p);
	if (cs->field_width > nlen)
		*str = malloc(cs->field_width + 1);
	else
		*str = malloc(nlen + 1);
	i = 0;
	if (*str != NULL)
	{
		if (cs->field_width > nlen && !cs->flag_minus)
			i = write_chars(*str, ' ', cs->field_width - nlen);
		i += write_ptr(*str + i, cs, p);
		if (cs->field_width > nlen && cs->flag_minus)
			i += write_chars(*str + i, ' ', cs->field_width - nlen);
		(*str)[i] = '\0';
	}
	return (i);
}

// int	convert_ptr(char **str, t_convspec *cs, void *p)
// {
// 	int				padding_left;
// 	int				padding_right;
// 	int				leading_zeros;
// 	int				nlen;
// 	uintptr_t		n;
// 	uintptr_t		magnitude;
// 	int				len;
// 	int				i;
// 	int				j;
// 	char			*baseset;
// 	char			*prefix;
// 	int				prefix_len;

// 	nlen = 0;
// 	if (!(p ==(void *) 0 && cs->flag_period && cs->precision == 0))
// 	{
// 		n = (uintptr_t)p;
// 		while(1)
// 		{
// 			nlen++;
// 			n /= 16;
// 			if (n == 0)
// 				break ;
// 		}
// 		magnitude = ptrpow(16, nlen - 1);
// 	}
// 	leading_zeros = 0;
// 	if (cs->flag_period && cs->precision > nlen)
// 		leading_zeros = cs->precision - nlen;
// 	nlen += leading_zeros;
// 	prefix = "0x";
// 	prefix_len = (int)ft_strlen(prefix);
// 	padding_left = 0;
// 	padding_right = 0;
// 	if (cs->field_width > nlen + prefix_len)
// 	{
// 		if (cs->flag_minus)
// 			padding_right = cs->field_width - nlen - prefix_len;
// 		else
// 			padding_left += cs->field_width - nlen - prefix_len;
// 	}
// 	len = padding_left + prefix_len + nlen + padding_right;
// 	*str = malloc((len + 1) * sizeof(char));
// 	if (*str != NULL)
// 	{
// 		i = 0;
// 		while (i < padding_left)
// 			(*str)[i++] = ' ';
// 		(*str)[i++] = '0';
// 		(*str)[i++] = 'x';
// 		j = 0;
// 		while (j < leading_zeros)
// 			(*str)[i + j++] = '0';
// 		i += j;
// 		if (nlen > 0)
// 		{
// 			baseset = BASESET_HEXL;
// 			n = (uintptr_t)p;
// 			while (1)
// 			{
// 				(*str)[i++] = baseset[n / magnitude];
// 				n %= magnitude;
// 				magnitude /= 16;
// 				if (magnitude == 0)
// 					break ;
// 			}
// 		}
// 		j = 0;
// 		while (j < padding_right)
// 			(*str)[i + j++] = ' ';
// 		(*str)[i + j] = '\0';
// 		if (i + j != len)
// 			ft_putendl_fd("OH NO!\n", 2);
// 	}
// 	return (len);
// }
