#include "libft.h"
#include "conversion.h"
#include <stdio.h>
#include <stdlib.h>

int	convert_str(char **str, t_convspec *cs, char *s)
{
	int				padding_left;
	int				padding_right;
	int				slen;
	int				len;
	int				i;
	int				j;

	slen = 0;
	if (cs->flag_period)
		while (s[slen] != '\0' && slen < cs->precision)
			slen++;
	else
		slen = (int)ft_strlen(s);
	padding_left = 0;
	padding_right = 0;
	if (cs->field_width > slen)
	{
		if (cs->flag_minus)
			padding_right = cs->field_width - slen;
		else
			padding_left += cs->field_width - slen;
	}
	len = padding_left + slen + padding_right;
	*str = malloc((len + 1) * sizeof(char));
	if (*str != NULL)
	{
		i = 0;
		while (i < padding_left)
			(*str)[i++] = ' ';
		j = 0;
		while (j < slen)
		{
			(*str)[i + j] = s[j];
			j++;
		}
		i += j;
		j = 0;
		while (j < padding_right)
			(*str)[i + j++] = ' ';
		(*str)[i + j] = '\0';
		if (i + j != len)
			ft_putendl_fd("OH NO!\n", 2);
	}
	return (len);
}
