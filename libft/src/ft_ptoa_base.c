/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenezes <jmenezes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:59:32 by jmenezes          #+#    #+#             */
/*   Updated: 2022/08/20 16:59:58 by jmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static int	nbrlen(void *ptr, uintptr_t rad)
{
	int			i;
	uintptr_t	p;

	p = (uintptr_t)ptr;
	i = 0;
	while (1)
	{
		i++;
		p /= rad;
		if (p == 0)
			return (i);
	}
}

char	*ft_ptoa_base(void *ptr, char *baseset)
{
	char		*str;
	int			i;
	uintptr_t	p;
	uintptr_t	rad;

	p = (uintptr_t)ptr;
	rad = (uintptr_t)ft_strlen(baseset);
	i = nbrlen(ptr, rad);
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
