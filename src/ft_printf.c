#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
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

int	convert_number(char **str, t_convspec *cs, int d);

unsigned int	ft_upow(unsigned int b, unsigned int e)
{
	int	n;

	n = 1;
	while (e > 0)
	{
		n *= b;
		e--;
	}
	return (n);
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

// todo: modify the following function to be used by str_to_convspec as a
//       validator to avoid allocation memory just for a substr duplication
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

int	put_number_conversion(t_convspec *cs, int n, int fd)
{
	char	*str;
	int		len;

	len = convert_number(&str, cs, n);
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
				int	len;

				cs = str_to_convspec(cstr);
				free(cstr);
				// if (cs->specifier == 'c')
				// 	cnt += put_char_conversion(str, cs);
				// if (cs->specifier == 's')
				// 	cnt += put_string_conversion(str, cs);
				// if (cs->specifier == 'p')
				// 	cnt += put_pointer_conversion(str, cs);
				// else // "diuxX"
					len = put_number_conversion(cs, va_arg(ap, int), fd);
				free(cs);
				cnt += len;
				fmt += len + 1;
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
