#include "conversion.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	put_char(char c)
{
	return ((int)write(1, &c, (int)1));
}

int	put_n_chars(char c, int n)
{
	int	cnt;

	cnt = 0;
	while (cnt < n)
		cnt += put_char(c);
	return (cnt);
}

int	put_str(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str != '\0')
		cnt += put_char(*(str++));
	return (cnt);
}

static int	cnt_leading_spaces(t_conversion *conv, int nbrlen)
{
	if (conv->min_width > nbrlen &&
		!conv->flag_minus &&
		(!conv->flag_zero || conv->flag_period))
		return (conv->min_width - nbrlen);
	return (0);
}

static int	cnt_leading_zeroes(t_conversion *conv, int nbrlen, int digitslen)
{
	if (conv->min_width > nbrlen &&
		conv->flag_zero &&
		!conv->flag_period &&
		!conv->flag_minus)
		return (conv->min_width - nbrlen);
	else if (conv->flag_period &&
		conv->precision > digitslen)
		return (conv->precision - digitslen);
	return (0);
}

static int	cnt_trailing_spaces(t_conversion *conv, int nbrlen)
{
	if (conv->flag_minus && conv->min_width > nbrlen)
		return (conv->min_width - nbrlen);
	return (0);
}

static int	unbrlen(unsigned int u, unsigned int rad)
{
	int	i;

	i = 0;
	while (1)
	{
		i++;
		u /= rad;
		if (u == 0)
			return (i);
	}
}

char	*ft_utoa_base(unsigned int u, char *baseset)
{
	char			*str;
	int				i;
	unsigned int	rad;

	rad = (unsigned int)ft_strlen(baseset);
	i = unbrlen(u, rad);
	str = malloc(i + 1);
	if (str != NULL)
	{
		str[i--] = '\0';
		while (1)
		{
			str[i--] = baseset[u % rad];
			u /= rad;
			if (u == 0)
				break ;
		}
	}
	return (str);
}

int	convert_uint(t_conversion *conv, unsigned int u)
{
	char	*digits;
	int		convlen;
	int		digitslen;
	int		nbrlen;
	int		zeroescnt;

	digits = ft_utoa_base(u, BASESET_DEC);
	if (digits == NULL)
		return (-1);
	digitslen = (int)ft_strlen(digits);
	zeroescnt = cnt_leading_zeroes(conv, digitslen, digitslen);
	nbrlen = digitslen + zeroescnt;
	convlen = put_n_chars(' ', cnt_leading_spaces(conv, nbrlen));
	convlen += put_n_chars('0', zeroescnt);
	convlen += put_str(digits);
	free(digits);
	convlen += put_n_chars(' ', cnt_trailing_spaces(conv, nbrlen));
	return (convlen);
}

// tests:

t_conversion	*new_conversion(char specifier)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	conv->specifier = specifier;
	conv->precision = 1;
	conv->min_width = 0;
	conv->flag_hash = 0;
	conv->flag_zero = 0;
	conv->flag_minus = 0;
	conv->flag_space = 0;
	conv->flag_plus = 0;
	conv->flag_period = 0;
	return (conv);
}

int	main(void)
{
    t_conversion	*conv;

	conv = new_conversion('u');
	convert_uint(conv, 42); // "42"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('u');
	conv->min_width = 5;
	convert_uint(conv, 42); // "   42"
	write(1, "\n", 1);

	conv = new_conversion('u');
	conv->min_width = 5;
	conv->flag_minus = 1;
	convert_uint(conv, 42); // "42   "
	write(1, "\n", 1);

	conv = new_conversion('u');
	conv->min_width = 5;
	conv->flag_zero = 1;
	convert_uint(conv, 42); // "00042"
	write(1, "\n", 1);

	conv = new_conversion('u');
	conv->flag_period = 1;
	conv->precision = 5;
	convert_uint(conv, 42); // "00042"
	write(1, "\n", 1);

	conv = new_conversion('u');
	conv->min_width = 10;
	conv->flag_period = 1;
	conv->precision = 5;
	convert_uint(conv, 42); // "     00042"
	write(1, "\n", 1);

	conv = new_conversion('u');
	conv->min_width = 10;
	conv->flag_minus = 1;
	conv->flag_period = 1;
	conv->precision = 5;
	convert_uint(conv, 42); // "00042     "
	write(1, "\n", 1);

	return (0);
}
