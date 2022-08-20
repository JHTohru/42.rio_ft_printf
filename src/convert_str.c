/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:49:36 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 18:41:08 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"

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
		convlen += (int)ft_putnchars(' ', spacescnt);
	convlen += (int)ft_putnstr(str, (size_t)slen);
	if (!conv->flag_minus)
		convlen += (int)ft_putnchars(' ', spacescnt);
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
//     char			*str;

//     str = "lorem ipsum";

// 	conv = new_conversion('s');
// 	convert_str(conv, str); // "lorem ipsum"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->min_width = 15;
// 	convert_str(conv, str); // "lorem ipsum    "
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->min_width = 15;
// 	conv->flag_minus = 1;
// 	convert_str(conv, str); // "    lorem ipsum"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->flag_period = 1;
// 	conv->precision = 0;
// 	convert_str(conv, str); // ""
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->flag_period = 1;
// 	conv->precision = 5;
// 	convert_str(conv, str); // "lorem"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->flag_period = 1;
// 	conv->precision = 1;
// 	convert_str(conv, str); // "l"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->min_width = 5;
// 	conv->flag_period = 1;
// 	conv->precision = 1;
// 	convert_str(conv, str); // "l    "
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('s');
// 	conv->min_width = 5;
// 	conv->flag_minus = 1;
// 	conv->flag_period = 1;
// 	conv->precision = 1;
// 	convert_str(conv, str); // "    l"
// 	write(1, "\n", 1);
// 	free(conv);

// 	return (0);
// }
