#include "libft.h"
#include "conversion.h"
#include <stdlib.h>
#define BASESET_DEC "0123456789"

int				ft_abs(int n);
unsigned int	upow(unsigned int b, unsigned int e);
unsigned int	ulog(unsigned int n, unsigned int b);
int				udigits(unsigned int n, int r);

int	writenchars(int (*wf)(int), int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
		i += wf(c);
	return (i);
}

int	writeuint(int (*wf)(int), unsigned int n, char *baseset)
{
	unsigned int	mag;
	unsigned int	rad;
	int				i;

	i = 0;
	rad = (unsigned int)ft_strlen(baseset);
	mag = upow(rad, ulog(n, rad));
	while (1)
	{
		i += wf(baseset[n / mag]);
		n %= mag;
		mag /= rad;
		if (mag == 0)
			break ;
	}
	return (i);
}

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

int	writenbr(int (*wf)(int), t_convspec *cs, int n)
{
	int	i;
	int	len;

	i = 0;
	if (n >= 0 && cs->flag_plus)
		i += wf('+');
	else if (n >= 0 && cs->flag_space)
		i += wf(' ');
	else if (n < 0)
		i += wf('-');
	len = udigits((unsigned int)ft_abs(n), 10);
	if (cs->flag_zero && !cs->flag_period && !cs->flag_minus
		&& cs->field_width > len + i)
		i += writenchars(wf, '0', cs->field_width - len - i);
	else if (cs->flag_period && cs->precision > len)
		i += writenchars(wf, '0', cs->precision - len);
	if (!cs->flag_period || cs->precision > 0 || n != 0)
		i += writeuint(wf, (unsigned int)ft_abs(n), BASESET_DEC);
	return (i);
}

int	convert_int(int (*wf)(int), t_convspec *cs, int n)
{
	int	nlen;
	int	i;

	nlen = nbrlen(cs, n);
	i = 0;
	if (cs->field_width > nlen && (!cs->flag_zero || cs->flag_period)
		&& !cs->flag_minus)
		i = writenchars(wf, ' ', cs->field_width - nlen);
	i += writenbr(wf, cs, n);
	if (cs->field_width > nlen && cs->flag_minus)
		i += writenchars(wf, ' ', cs->field_width - nlen);
	return (i);
}
