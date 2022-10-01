/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:48:16 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/28 00:17:14 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

int	convert_ptr(t_conversion *conv, void *ptr)
{
	char	*digits;
	int		convlen;
	int		nbrlen;
	int		spacescnt;

	if (ptr == NULL)
		return (ft_putstr(NULL_PTR));
	digits = ft_ptoa_base(ptr, BASESET_HEXL);
	if (digits == NULL)
		return (-1);
	nbrlen = (int)ft_strlen(digits) + 2;
	spacescnt = 0;
	if (conv->min_width > nbrlen)
		spacescnt = conv->min_width - nbrlen;
	convlen = 0;
	if (!conv->flag_minus)
		convlen += (int)ft_putnchars(' ', spacescnt);
	convlen += (int)ft_putstr("0x");
	convlen += (int)ft_putstr(digits);
	free(digits);
	if (conv->flag_minus)
		convlen += (int)ft_putnchars(' ', spacescnt);
	return (convlen);
}
