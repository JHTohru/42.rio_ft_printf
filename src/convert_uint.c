#include "libft.h"
#include "conversion.h"
#include <stdlib.h>
#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")
#define BASESET_HEXU (BASESET_DEC "ABCDEF")

int	write_chars(char *str, int c, int n);
int	uwrite(char *str, unsigned int n, char *baseset);
int	udigits(unsigned int n, int r);

int	nbrlen(t_convspec *cs, unsigned int n)
{
	int	len;

	len = 0;
	if (!cs->flag_period || cs->precision > 0 || n != 0)
		len = udigits(n, 10);
	if (cs->flag_period && cs->precision > len)
		len = cs->precision;
	if ((cs->specifier == 'x' || cs->specifier == 'X') && cs->flag_hash)
		len += 2;
	return (len);
}

int	write_nbr(char *str, t_convspec *cs, int n)
{
	int		len;
	int		i;
	char	*baseset;

	if (cs->specifier == 'x' || cs->specifier == 'X')
		len = udigits(n, 16);
	else
		len = udigits(n, 10);
	i = 0;
	if ((cs->specifier == 'x' || cs->specifier == 'X') && cs->flag_hash)
	{
		str[i++] = '0';
		str[i++] = cs->specifier;
	}
	if (cs->flag_zero && !cs->flag_period && !cs->flag_minus
		&& cs->field_width > len + i)
		i += write_chars(str + i, '0', cs->field_width - len - i);
	else if (cs->flag_period && cs->precision > len)
		i += write_chars(str + i, '0', cs->precision - len);
	if (!cs->flag_period || cs->precision != 0 || n != 0)
	{
		if (cs->specifier == 'x')
			baseset = BASESET_HEXL;
		else if (cs->specifier == 'X')
			baseset = BASESET_HEXU;
		else
			baseset = BASESET_DEC;
		i += uwrite(str + i, n, baseset);
	}
	return (i);		
}

int	convert_uint(char **str, t_convspec *cs, unsigned int n)
{
	int	nlen;
	int	i;

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
