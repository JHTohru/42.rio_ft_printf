#include "libft.h"
#include "conversion.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	convert_char(char **str, t_convspec *cs, char c)
{
	int				padding_left;
	int				padding_right;
	int				len;
	int				i;
	int				j;

	padding_left = 0;
	padding_right = 0;
	if (cs->field_width > 1)
	{
		if (cs->flag_minus)
			padding_right = cs->field_width - 1;
		else
			padding_left += cs->field_width - 1;
	}
	len = padding_left + padding_right + 1;
	*str = malloc((len + 1) * sizeof(char));
	if (*str != NULL)
	{
		i = 0;
		while (i < padding_left)
			(*str)[i++] = ' ';
		(*str)[i++] = c;
		j = 0;
		while (j < padding_right)
			(*str)[i + j++] = ' ';
		(*str)[i + j] = '\0';
		if (i + j != len)
			ft_putendl_fd("OH NO!\n", 2);
	}
	return (len);
}
