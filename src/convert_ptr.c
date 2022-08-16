#include "conversion.h"
#include <stdint.h>
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

static int	ptrlen(uintptr_t p, uintptr_t rad)
{
	uintptr_t	i;

	i = 0;
	while (1)
	{
		i++;
		p /= rad;
		if (p == 0)
			return (i);
	}
}

char	*ft_ptoa_base(uintptr_t p, char *baseset)
{
	char		*str;
	int			i;
	uintptr_t	rad;

	rad = (uintptr_t)ft_strlen(baseset);
	i = ptrlen(p, rad);
	str = malloc(i + 1);
	if (str != NULL)
	{
		str[i--] = '\0';
		while (1)
		{
			str[i--] = baseset[p % rad];
			p /= rad;
			if (p == 0)
				break ;
		}
	}
	return (str);
}

int	convert_ptr(t_conversion *conv, uintptr_t p)
{
	char	*digits;
	int		convlen;
	int		nbrlen;
	int		spacescnt;

	digits = ft_ptoa_base(p, BASESET_HEXL);
	if (digits == NULL)
		return (-1);
	nbrlen = (int)ft_strlen(digits) + 2;
	spacescnt = 0;
	if (conv->min_width > nbrlen)
		spacescnt = conv->min_width - nbrlen;
	convlen = 0;
	if (conv->flag_minus)
		convlen += put_n_chars(' ', spacescnt);
	convlen += put_str("0x");
	convlen += put_str(digits);
	free(digits);
	if (!conv->flag_minus)
		convlen += put_n_chars(' ', spacescnt);
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
    uintptr_t		p;

	conv = new_conversion('p');
	convert_ptr(conv, 0); // "0x0"
	write(1, "\n", 1);
	free(conv);

    p = 3735928559;

	conv = new_conversion('p');
	convert_ptr(conv, p); // "0xdeadbeef"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('p');
	conv->min_width = 13;
	convert_ptr(conv, p); // "   0xdeadbeef"
	write(1, "\n", 1);

	conv = new_conversion('p');
	conv->min_width = 13;
	conv->flag_minus = 1;
	convert_ptr(conv, p); // "0xdeadbeef   "
	write(1, "\n", 1);

	return (0);
}
