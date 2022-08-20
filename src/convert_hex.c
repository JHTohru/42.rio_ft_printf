/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:36:00 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 19:13:40 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"
#include <stdlib.h>

int	cnt_leading_spaces(t_conversion *conv, int nbrlen);
int	cnt_leading_zeroes(t_conversion *conv, int nbrlen, int digitslen);
int	cnt_trailing_spaces(t_conversion *conv, int nbrlen);

int	convert_hex(t_conversion *conv, unsigned int u)
{
	char	*digits;
	int		convlen;
	int		nbrlen;
	int		zcnt;

	if (conv->specifier == 'x')
		digits = ft_utoa_base(u, BASESET_HEXL);
	else
		digits = ft_utoa_base(u, BASESET_HEXU);
	if (digits == NULL)
		return (-1);
	nbrlen = (int)ft_strlen(digits);
	if (conv->flag_hash)
		nbrlen += 2;
	zcnt = cnt_leading_zeroes(conv, nbrlen, (int)ft_strlen(digits));
	convlen = (int)ft_putnchars(' ', cnt_leading_spaces(conv, nbrlen + zcnt));
	if (conv->flag_hash && conv->specifier == 'x')
		convlen += (int)ft_putstr("0x");
	else if (conv->flag_hash)
		convlen += (int)ft_putstr("0X");
	convlen += (int)ft_putnchars('0', zcnt);
	convlen += (int)ft_putstr(digits);
	free(digits);
	convlen += (int)ft_putnchars(' ', cnt_trailing_spaces(conv, nbrlen + zcnt));
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
//     unsigned int    u;

//     u = 3735928559;

// 	conv = new_conversion('x');
// 	convert_hex(conv, u); // "deadbeef"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('x');
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "0xdeadbeef"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
// 	convert_hex(conv, u); // "     deadbeef"
// 	write(1, "\n", 1);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "   0xdeadbeef"
// 	write(1, "\n", 1);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "deadbeef     "
// 	write(1, "\n", 1);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "0xdeadbeef   "
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 13;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 13;
//     conv->flag_hash = 1;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "0x000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0x00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "     00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "   0x00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000deadbeef     "
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0x00000deadbeef   "
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	convert_hex(conv, u); // "DEADBEEF"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('X');
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "0XDEADBEEF"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
// 	convert_hex(conv, u); // "     DEADBEEF"
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "   0XDEADBEEF"
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "DEADBEEF     "
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "0XDEADBEEF   "
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 13;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 13;
//     conv->flag_hash = 1;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "0X000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0X00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "     00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "   0X00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000DEADBEEF     "
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0X00000DEADBEEF   "
// 	write(1, "\n", 1);

// 	return (0);
// }
