/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:47:37 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 19:15:46 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"
#include <stdlib.h>

int	cnt_leading_spaces(t_conversion *conv, int nbrlen);
int	cnt_leading_zeroes(t_conversion *conv, int nbrlen, int digitslen);
int	cnt_trailing_spaces(t_conversion *conv, int nbrlen);

int	convert_int(t_conversion *conv, int n)
{
	char	*digits;
	int		convlen;
	int		nbrlen;
	int		zeroescnt;

	digits = ft_utoa_base((unsigned int)ft_abs(n), BASESET_DEC);
	if (digits == NULL)
		return (-1);
	nbrlen = (int)ft_strlen(digits);
	if (n < 0 || conv->flag_plus || conv->flag_space)
		nbrlen++;
	zeroescnt = cnt_leading_zeroes(conv, nbrlen, (int)ft_strlen(digits));
	nbrlen += zeroescnt;
	convlen = (int)ft_putnchars(' ', cnt_leading_spaces(conv, nbrlen));
	if (n < 0)
		convlen += (int)ft_putchar('-');
	else if (conv->flag_plus)
		convlen += (int)ft_putchar('+');
	else if (conv->flag_space)
		convlen += (int)ft_putchar(' ');
	convlen += (int)ft_putnchars('0', zeroescnt);
	convlen += (int)ft_putstr(digits);
	free(digits);
	convlen += (int)ft_putnchars(' ', cnt_trailing_spaces(conv, nbrlen));
	return (convlen);
}

// tests:

// t_conversion	*new_conversion(char specifier)
// {
// 	t_conversion	*conv;

// 	conv = malloc(sizeof(t_conversion));
// 	conv->specifier = specifier;
// 	conv->precision = 1;
// 	conv->min_width = 0;
// 	conv->flag_hash = 0;
// 	conv->flag_zero = 0;
// 	conv->flag_minus = 0;
// 	conv->flag_space = 0;
// 	conv->flag_plus = 0;
// 	conv->flag_period = 0;
// 	return (conv);
// }

// int	main(void)
// {
//     t_conversion	*conv;

// 	conv = new_conversion('d');
// 	convert_int(conv, -42); // "-42"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('d');
// 	conv->min_width = 5;
// 	convert_int(conv, -42); // "  -42"
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->min_width = 5;
// 	conv->flag_minus = 1;
// 	convert_int(conv, -42); // "-42  "
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->min_width = 5;
// 	conv->flag_zero = 1;
// 	convert_int(conv, -42); // "-0042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_int(conv, -42); // "-00042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->min_width = 10;
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_int(conv, -42); // "    -00042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->min_width = 10;
// 	conv->flag_minus = 1;
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_int(conv, -42); // "-00042    "
// 	write(1, "\n", 1);

// 	conv = new_conversion('d');
// 	conv->flag_period = 1;
// 	conv->precision = 0;
// 	convert_int(conv, -42); // "-42"
// 	write(1, "\n", 1);

// 	return (0);
// }
