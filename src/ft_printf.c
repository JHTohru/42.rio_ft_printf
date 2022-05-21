#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

typedef struct s_convspec {
	char			specifier;
	int				precision;
	int				width_min;
	unsigned char	flag_hash: 1;
	unsigned char	flag_zero: 1;
	unsigned char	flag_minus: 1;
	unsigned char	flag_space: 1;
	unsigned char	flag_plus: 1;
	unsigned char	flag_dot: 1;
}	t_convspec;

char	*strnchar(char c, size_t len)
{
	return (ft_memset(ft_strnew(len + 1), c, len + 1));
}

char	*strjoindel(char **str1, char **str2)
{
	char	*str;

	str = ft_strjoin(*str1, *str2);
	ft_strdel(str1);
	ft_strdel(str2);
	return (str);
}

void	strprefix(char *pref, char **str)
{
	char	*tmp;

	tmp = ft_strjoin(pref, *str);
	ft_strdel(str);
	*str = tmp;
}

void	strpadl(char **str, size_t spcnt)
{
	char	*pad;

	pad = strnchar(' ', spcnt);
	*str = strjoindel(&pad, str);
}

void	strpadr(char **str, size_t spcnt)
{
	char	*pad;

	pad = strnchar(' ', spcnt);
	*str = strjoindel(str, &pad);
}

void	nbrpad(char **str, size_t n)
{
	char	*pad;
	char	*tmp;

	if (**str == '-')
	{
		pad = strnchar('0', n + 1);
		pad[0] = '-';
	}
	else
		pad = strnchar('0', n);
	tmp = NULL;
	if (pad != NULL)
	{
		if (**str == '-')
			tmp = ft_strjoin(pad, *str + 1);
		else
			tmp = ft_strjoin(pad, *str);
	}
	ft_strdel(str);
	*str = tmp;
}

char	*convert_char(t_convspec *cs, char c)
{
	char	*str;

	str = ft_strnew(2);
	if (str != NULL)
	{
		*str = c;
		if ((size_t)cs->width_min > 1)
		{
			if (cs->flag_minus)
				strpadr(&str, (size_t)cs->width_min - 1);
			else
				strpadl(&str, (size_t)cs->width_min - 1);
		}
	}
	return (str);
}

char	*convert_str(t_convspec *cs, char *src)
{
	char	*str;
	size_t	len;

	if (cs->flag_dot)
		len = (size_t)cs->precision;
	else
		len = ft_strlen(src);
	str = ft_strndup(src, len);
	if (str != NULL && (size_t)cs->width_min > len)
	{
		if (cs->flag_minus)
			strpadr(&str, (size_t)cs->width_min - len);
		else
			strpadl(&str, (size_t)cs->width_min - len);
	}
	return (str);
}

char	*convert_ptr2(void *p, int lmin)
{
	char	*str;
	int		len;

	str = ft_ptoa(p);
	if (str != NULL)
	{
		len = (int)ft_strlen(str);
		if (lmin > len)
			nbrpad(&str, lmin - len);
		strprefix("0x", &str);
	}
	return (str);
}

char	*convert_ptr(t_convspec *cs, void *p)
{
	char	*str;
	int		len;

	str = convert_ptr2(p, cs->precision);
	if (str != NULL)
	{
		len = (int)ft_strlen(str);
		if (cs->width_min > len)
		{
			if (cs->flag_minus)
				strpadr(&str, cs->width_min - len);
			else
				strpadl(&str, cs->width_min - len);
		}
	}
	return (str);
}

char	*convert_int2(int n, int lmin)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa(n);
	len = (int)ft_strlen(nbr);
	if (lmin > len)
		nbrpad(&nbr, lmin - len);
	return (nbr);
}

char	*convert_int(t_convspec *cs, int n)
{
	char	*nbr;
	size_t	len;
	int		lmin;

	lmin = 1;
	if (cs->flag_dot)
	{
		lmin = cs->precision;
		if (n < 0)
			lmin++;
	}
	else if (cs->flag_zero && !cs->flag_minus)
		lmin = cs->width_min;
	nbr = convert_int2(n, lmin);
	if (n >= 0)
	{
		if (cs->flag_plus)
			strprefix("+", &nbr);
		else if (cs->flag_space)
			strprefix(" ", &nbr);
	}
	len = (int)ft_strlen(nbr);
	if ((!cs->flag_zero || cs->flag_dot) && (size_t)cs->width_min > len)
	{
		if (cs->flag_minus)
			strpadr(&nbr, cs->width_min - len);
		else
			strpadl(&nbr, cs->width_min - len);
	}
	return (nbr);
}

char	*convert_uint_dec(t_convspec *cs, unsigned int n)
{
	// char	*nbr;
	// size_t	len;

	// nbr = ft_uitoa(n);
	// len = ft_strlen(nbr);
	// if (cs->flag_dot && (size_t)cs->precision > len)
	// {
	// 	prependzeroes(&nbr, (size_t)cs->precision - len);
	// }
	// else if (!cs->flag_dot && !cs->flag_minus 
	// 	&& cs->flag_zero && (size_t)cs->width_min > len)
	// 	prependzeroes(&nbr, (size_t)cs->width_min - len);
	// return (nbr);

	// todo: code stuff
	(void)cs;
	(void)n;
	return (NULL);
}

char	*convert_uint_hex(t_convspec *cs, unsigned int n)
{
	// todo: code stuff
	(void)cs;
	(void)n;
	return (NULL);
}

char	*convert(t_convspec *cs, void *arg)
{
	char	*str;

	if (cs->specifier == 'c')
		str = convert_char(cs, *((int *)arg));
	else if (cs->specifier == 's')
		str = convert_str(cs, (char *)arg);
	else if (cs->specifier == 'p')
		str = convert_ptr(cs, arg);
	else if (cs->specifier == 'd' || cs->specifier == 'i')
		str = convert_int(cs, *((int *)arg));
	else if (cs->specifier == 'u')
		str = convert_uint_dec(cs, *((unsigned int *)arg));
	else
		str = convert_uint_hex(cs, *((unsigned int *)arg));
	return (str);
}

int	isflag(char c)
{
	return (c == '#'
		|| c == '+'
		|| c == '-'
		|| c == '0'
		|| c == ' ');
}

int	isspecifier(char c)
{
	return (c == 'c'
		|| c == 's'
		|| c == 'p'
		|| c == 'd'
		|| c == 'i'
		|| c == 'u'
		|| c == 'x'
		|| c == 'X');		
}

char	*extract_convspec_str(const char *str)
{
	size_t	len;

	if (*str != '%')
		return (NULL);
	str++;
	len = 0;
	while (isflag(str[len]))
		len++;
	while (ft_isdigit(str[len]))
		len++;
	if (str[len] == '.')
		len++;
	while (ft_isdigit(str[len]))
		len++;
	if (!isspecifier(str[len]))
		return (NULL);
	len++;
	return (ft_strndup(str, len));
}

t_convspec	*str_to_convspec(char *str)
{
	t_convspec	*cs;

	cs = ft_calloc(1, sizeof(t_convspec));
	if (cs != NULL)
	{
		while (isflag(*str))
		{
			if (*str == '#')
				cs->flag_hash = 1;
			else if (*str == '+')
				cs->flag_plus = 1;
			else if (*str == '-')
				cs->flag_minus = 1;
			else if (*str == '0')
				cs->flag_zero = 1;
			else if (*str == ' ')
				cs->flag_space = 1;
			str++;
		}
		if (ft_isdigit(*str))
			cs->width_min = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		if (*str == '.')
			cs->flag_dot = 1;
		if (ft_isdigit(*str))
			cs->precision = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		cs->specifier = *str;
	}
	return (cs);
}

int	put_conversion(t_convspec *cs, void *arg, int fd)
{
	char	*str;
	int		len;

	str = convert(cs, arg);
	len = (int)ft_strlen(str);
	ft_putstr_fd(str, fd);
	free(str);
	return (len);
}

int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	int			cnt;
	char		*cstr;
	t_convspec	*cs;

	cnt = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			cstr = extract_convspec_str(fmt);
			if (cstr != NULL)
			{
				cs = str_to_convspec(cstr);
				cnt += put_conversion(cs, va_arg(ap, void *), fd);
				free(cs);
				fmt += ft_strlen(cstr) + 1;
				free(cstr);
				continue ;
			}
			if (fmt[1] == '%')
				fmt++;
		}
		ft_putchar_fd(*fmt, fd);
		cnt++;
		fmt++;
	}
	return (cnt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, fmt);
	res = ft_vdprintf(1, fmt, ap);
	va_end(ap);
	return (res);
}
