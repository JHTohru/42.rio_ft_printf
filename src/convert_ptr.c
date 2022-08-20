/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:48:16 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 17:07:55 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "conversion.h"
#include <stdint.h>
#include <stdlib.h>

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
		convlen += (int)ft_putnchars(' ', spacescnt);
	convlen += (int)ft_putstr("0x");
	convlen += (int)ft_putstr(digits);
	free(digits);
	if (!conv->flag_minus)
		convlen += (int)ft_putnchars(' ', spacescnt);
	return (convlen);
}

// // tests:

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
//     uintptr_t		p;

// 	conv = new_conversion('p');
// 	convert_ptr(conv, 0); // "0x0"
// 	write(1, "\n", 1);
// 	free(conv);

//     p = 3735928559;

// 	conv = new_conversion('p');
// 	convert_ptr(conv, p); // "0xdeadbeef"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('p');
// 	conv->min_width = 13;
// 	convert_ptr(conv, p); // "   0xdeadbeef"
// 	write(1, "\n", 1);

// 	conv = new_conversion('p');
// 	conv->min_width = 13;
// 	conv->flag_minus = 1;
// 	convert_ptr(conv, p); // "0xdeadbeef   "
// 	write(1, "\n", 1);

// 	return (0);
// }
