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

int	put_n_str(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		put_char(str[i++]);
	return (n);
}

int	convert_str(t_conversion *conv, char *str)
{
	int	convlen;
	int	slen;
	int	spacescnt;

	slen = 0;
	if (conv->flag_period)
		while (str[slen] != '\0' && slen < conv->precision)
			slen++;
	else
		slen = (int)ft_strlen(str);
	spacescnt = 0;
	if (conv->min_width > slen)
		spacescnt = conv->min_width - slen;
	convlen = 0;
	if (conv->flag_minus)
		convlen += put_n_chars(' ', spacescnt);
	convlen += put_n_str(str, slen);
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
    char			*str;

    str = "lorem ipsum";

	conv = new_conversion('s');
	convert_str(conv, str); // "lorem ipsum"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->min_width = 15;
	convert_str(conv, str); // "lorem ipsum    "
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->min_width = 15;
	conv->flag_minus = 1;
	convert_str(conv, str); // "    lorem ipsum"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->flag_period = 1;
	conv->precision = 0;
	convert_str(conv, str); // ""
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->flag_period = 1;
	conv->precision = 5;
	convert_str(conv, str); // "lorem"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->flag_period = 1;
	conv->precision = 1;
	convert_str(conv, str); // "l"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->min_width = 5;
	conv->flag_period = 1;
	conv->precision = 1;
	convert_str(conv, str); // "l    "
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('s');
	conv->min_width = 5;
	conv->flag_minus = 1;
	conv->flag_period = 1;
	conv->precision = 1;
	convert_str(conv, str); // "    l"
	write(1, "\n", 1);
	free(conv);

	return (0);
}
