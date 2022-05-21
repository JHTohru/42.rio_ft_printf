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

char	*ft_strncpy(char *dst, char* src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i] = '\0';
	return (dst);
}

#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")
#define BASESET_HEXU (BASESET_DEC "ABCDEF")

int	convert_number(char **str, t_convspec *cs, int d)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				flag_zero;
	int				d_is_negative;
	unsigned int	n;
	unsigned int	m;
	int				nlen;
	unsigned int	magnitude;
	int				len;
	int				i;
	int				j;
	int				raddix;
	char			*baseset;

	if (cs->specifier == 'x' || cs->specifier == 'X')
		raddix = 16;
	else
		raddix = 10;
	d_is_negative = d < 0;
	if (d_is_negative)
		n = -d;
	else
		n = d;
	nlen = 0;
	m = n;
	while(1)
	{
		nlen++;
		m /= raddix;
		if (m == 0)
			break ;
	}
	magnitude = ft_upow(raddix, nlen - 1);
	// printf("1st nlen = %d\n", nlen);
	leading_zeros = 0;
	if (cs->flag_dot && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	padding_left = 0;
	if (cs->specifier == 'd' || cs->specifier == 'i')
	{
		if (d_is_negative || cs->flag_plus)
			nlen++;
		else if (cs->flag_space)
			padding_left++;
	}
	else if ((cs->specifier == 'x' || cs->specifier == 'X') && cs->flag_hash)
	{
		nlen += 2; // preffix length
	}
	flag_zero = 0;
	if (cs->flag_zero && !cs->flag_dot && !cs->flag_minus && cs->width_min > nlen)
	{
		flag_zero = 1;
		leading_zeros = cs->width_min - nlen - padding_left;
	}
	nlen += leading_zeros;
	padding_right = 0;
	if (cs->width_min > nlen)
	{
		if (cs->flag_minus)
			padding_right = cs->width_min - nlen;
		else if (!flag_zero)
			padding_left += cs->width_min - nlen;
	}
	len = padding_left + nlen + padding_right;
	// printf("padding_left = %d\n", padding_left);
	// printf("padding_right = %d\n", padding_right);
	// printf("leading_zeros = %d\n", leading_zeros);
	// printf("nlen = %d\n", nlen);
	// printf("len = %d\n", len);
	// printf("size = %d\n", len + 1);
	*str = malloc((len + 1) * sizeof(char));
	if (*str != NULL)
	{	
		i = 0;
		while (i < padding_left)
			(*str)[i++] = ' ';
		if (cs->specifier == 'd' || cs->specifier == 'i')
		{
			if (d_is_negative)
				(*str)[i++] = '-';
			else if (cs->flag_plus)
				(*str)[i++] = '+';
		}
		else if (raddix == 16 && cs->flag_hash)
		{
			printf("raddix = %d\n", raddix);

			if (cs->specifier == 'x')
				ft_strncpy(*str + i, "0x", 2);
			else
				ft_strncpy(*str + i, "0X", 2);
			i += 2;
		}
		j = 0;
		while (j < leading_zeros)
			(*str)[i + j++] = '0';
		i += j;
		m = n;
		// printf("\n####################\n\n");
		if (cs->specifier == 'd' || cs->specifier == 'i' || cs->specifier == 'u')
			baseset = BASESET_DEC;
		else if (cs->specifier == 'x')
			baseset = BASESET_HEXL;
		else // cs->specifier == 'X'
			baseset = BASESET_HEXU;
		while (1)
		{
			// printf("i = %d\n", i);
			// printf("m = %d\n", m);
			// printf("magnitude = %d\n", magnitude);
			// printf("c = %c\n", m / magnitude + '0');
			// printf("\n--------------------\n\n");
			(*str)[i++] = baseset[m / magnitude];
			m %= magnitude;
			magnitude /= raddix;
			if (magnitude == 0)
				break ;
		}
		// printf("\n####################\n\n");
		j = 0;
		while (j < padding_right)
			(*str)[i + j++] = ' ';
		(*str)[i + j] = '\0'; // desnecessário se str for alocado com calloc
		if (i + j != len)
			ft_putendl_fd("OH NO!\n", 2);
	}
	return (nlen);
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
