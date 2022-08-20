/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:52:36 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 17:04:19 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"
#include <stdlib.h>

int	cnt_leading_spaces(t_conversion *conv, int nbrlen);
int	cnt_leading_zeroes(t_conversion *conv, int nbrlen, int digitslen);
int	cnt_trailing_spaces(t_conversion *conv, int nbrlen);

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
	convlen = (int)ft_putnchars(' ', cnt_leading_spaces(conv, nbrlen));
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

// 	conv = new_conversion('u');
// 	convert_uint(conv, 42); // "42"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('u');
// 	conv->min_width = 5;
// 	convert_uint(conv, 42); // "   42"
// 	write(1, "\n", 1);

// 	conv = new_conversion('u');
// 	conv->min_width = 5;
// 	conv->flag_minus = 1;
// 	convert_uint(conv, 42); // "42   "
// 	write(1, "\n", 1);

// 	conv = new_conversion('u');
// 	conv->min_width = 5;
// 	conv->flag_zero = 1;
// 	convert_uint(conv, 42); // "00042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('u');
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_uint(conv, 42); // "00042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('u');
// 	conv->min_width = 10;
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_uint(conv, 42); // "     00042"
// 	write(1, "\n", 1);

// 	conv = new_conversion('u');
// 	conv->min_width = 10;
// 	conv->flag_minus = 1;
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_uint(conv, 42); // "00042     "
// 	write(1, "\n", 1);

// 	return (0);
// }
