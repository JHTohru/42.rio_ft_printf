#include "libft.h"
#include "conversion.h"
#include <stdlib.h>
#define BASESET_DEC "0123456789"

int	ft_abs(int n);
int	write_chars(char *str, int c, int n);
int	uwrite(char *str, unsigned int n, char *baseset);
int	udigits(unsigned int n, int r);

int	nbrlen(t_convspec *cs, int n)
{
	int	len;

	if (n == 0 && cs->flag_period && cs->precision == 0)
		len = 0;
	else
		len = udigits((unsigned int)ft_abs(n), 10);
	if (cs->flag_period && cs->precision > len)
		len = cs->precision;
	if (n < 0 || cs ->flag_plus || cs->flag_space)
		len++;
	return (len);
}

int	write_nbr(char *str, t_convspec *cs, int n)
{
	int	i;
	int	len;

	len = udigits((unsigned int)ft_abs(n), 10);
	i = 0;
	if (n >= 0 && cs->flag_plus)
		str[i++] = '+';
	else if (n >= 0 && cs->flag_space)
		str[i++] = ' ';
	else if (n < 0)
		str[i++] = '-';
	if (cs->flag_zero && !cs->flag_period && !cs->flag_minus
		&& cs->field_width > len + i)
		i += write_chars(str + i, '0', cs->field_width - len - i);
	else if (cs->flag_period && cs->precision > len)
		i += write_chars(str + i, '0', cs->precision - len);
	if (!cs->flag_period || cs->precision > 0 || n != 0)
		i += uwrite(str + i, (unsigned int)ft_abs(n), BASESET_DEC);
	return (i);
}

int	convert_int(char **str, t_convspec *cs, int n)
{
	int	nlen;
	int i;

	nlen = nbrlen(cs, n);
	if (cs->field_width > nlen)
		*str = malloc(cs->field_width + 1);
	else
		*str = malloc(nlen + 1);
	i = 0;
	if (*str != NULL)
	{
		if (cs->field_width > nlen && (!cs->flag_zero || cs->flag_period)
			&& !cs->flag_minus)
			i = write_chars(*str, ' ', cs->field_width - nlen);
		i += write_nbr(*str + i, cs, n);
		if (cs->field_width > nlen && cs->flag_minus)
			i += write_chars(*str + i, ' ', cs->field_width - nlen);
		(*str)[i] = '\0';
	}
	// todo: o que retornar quando *str == NULL?
	return (i);
}
