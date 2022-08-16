#include "conversion.h"
#include <stdlib.h>
#include <unistd.h>

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

int	convert_char(t_conversion *conv, char c)
{
	int	convlen;
	int	spacescnt;

	spacescnt = 0;
	if (conv->min_width > 1)
		spacescnt += conv->min_width - 1;
	convlen = 0;
	if (conv->flag_minus)
		convlen += put_n_chars(' ', spacescnt);
	convlen += put_char(c);
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
    char			c;

    c = 'x';

	conv = new_conversion('c');
	convert_char(conv, c); // "x"
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('c');
	conv->min_width = 5;
	convert_char(conv, c); // "x    "
	write(1, "\n", 1);
	free(conv);

	conv = new_conversion('c');
	conv->min_width = 5;
	conv->flag_minus = 1;
	convert_char(conv, c); // "    x"
	write(1, "\n", 1);
	free(conv);

	return (0);
}
