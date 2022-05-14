#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#define STDOUT_FD 1
#define DEC_BASE_SET "0123456789"
#define HEX_LOWER_BASE_SET "0123456789abcdef"
#define HEX_UPPER_BASE_SET "0123456789ABCDEF"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(src);
	if (len < n)
		n = len;
	dup = ft_calloc(n + 1, sizeof(char));
	if (dup != NULL)
		ft_strlcpy(dup, src, n + 1);
	return (dup);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(src) + 1;
	dup = ft_calloc(size, sizeof(char));
	if (dup != NULL)
		ft_strlcpy(dup, src, size);
	return (dup);
}

int	isbigendian(void)
{
	unsigned int	i;

	i = 1;
	return (((char *)&i)[0] == 0);
}

static void	ptoa_lilendian(const void *s, char *dst)
{
	size_t	i;

	i = 0;
	while (i < sizeof(void *))
	{
		dst[i] = ((char *)&s)[sizeof(void *) + i - 1];
		if (i == 0)
			break;
		i--;
	}
}

static void	ptoa_bigendian(const void *s, char *dst)
{
	size_t	i;

	i = 0;
	while (i < sizeof(void *))
	{
		dst[i] = ((char *)&s)[i];
		i++;
	}
}

char	*ft_ptoa(const void *s)
{
	char	*str;

	str = ft_calloc(sizeof(void *) + 1, sizeof(char));
	if (str != NULL)
	{
		if (isbigendian())
			ptoa_bigendian(s, str);
		else
			ptoa_lilendian(s, str);
	}
	return (str);
}

int	digits_cnt(unsigned int n, unsigned int rad)
{
	int	cnt;

	cnt = 0;
	while (1)
	{
		n /= rad;
		cnt++;
		if (n == 0)
			break ;
	}
	return (cnt);
}

char	*ft_itoa_base(int n, const char *base)
{
	char	*str;
	int		len;
	int		n_is_negative;
	int		rad;
	int		i;

	rad = (int)ft_strlen(base);
	n_is_negative = n < 0;
	if (n_is_negative)
		len = digits_cnt((unsigned int)-n, (unsigned int)rad) + 1;
	else
		len = digits_cnt((unsigned int)n, (unsigned int)rad);
	str = ft_calloc(len + 1, sizeof(char));
	if (str != NULL)
	{
		i = len - 1;
		while (1)
		{
			if (n_is_negative)
				str[i] = base[-n % rad];
			else
				str[i] = base[n % rad];
			i--;
			n /= rad;
			if (n == 0)
				break ;
		}
		if (n_is_negative)
			str[i] = '-';
	}
	return (str);
}

char	*ft_uitoa_base(unsigned int n, const char *base)
{
	char			*str;
	unsigned int	len;
	unsigned int	rad;
	unsigned int	i;

	rad = (unsigned int)ft_strlen(base);
	len = (unsigned int)digits_cnt(n, rad);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str != NULL)
	{
		i = len - 1;
		while (1)
		{
			str[i--] = base[n % rad];
			n /= rad;
			if (n == 0)
				break ;
		}
	}
	return (str);
}

static int	putconv(char c, va_list ap)
{
	char	*str;
	int		len;

	if (c == '%')
	{
		ft_putchar_fd(c, STDOUT_FD);
		return (1);	
	}
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), STDOUT_FD);
		return (1);
	}
	if (c == 's')
		str = ft_strdup(va_arg(ap, char *));
	else if (c == 'p')
		str = ft_ptoa(va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		str = ft_itoa_base(va_arg(ap, int), DEC_BASE_SET);
	else if (c == 'u')
		str = ft_uitoa_base(va_arg(ap, unsigned int), DEC_BASE_SET);
	else if (c == 'x')
		str = ft_uitoa_base(va_arg(ap, unsigned int), HEX_LOWER_BASE_SET);
	else if (c == 'X')
		str = ft_uitoa_base(va_arg(ap, unsigned int), HEX_UPPER_BASE_SET);
	ft_putstr_fd(str, STDOUT_FD);
	len = (int)ft_strlen(str);
	free(str);
	return (len);
}

static int	ft_vprintf(const char *fmt, va_list ap)
{
	int		len;

	len = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
			len += putconv(*(++fmt), ap);
		else
		{
			ft_putchar_fd(*fmt, STDOUT_FD);
			len++;
		}
		fmt++;
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, fmt);
	res = ft_vprintf(fmt, ap);
	va_end(ap);
	return (res);
}
