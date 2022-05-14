#include "libft.h"
#include <stdarg.h>
#define STDOUT_FD 1
#define DEC_BASE_SET "0123456789"
#define HEX_LOWER_BASE_SET "0123456789abcdef"
#define HEX_UPPER_BASE_SET "0123456789ABCDEF"

static int	ft_putconv(char c, va_list ap)
{
	char	*str;
	int		len;

	if (c == 'c')
		str = ft_strndup(va_arg(ap, char), 1);
	else if (c == 's')
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
	else if (c == '%')
		str = ft_strndup("%");
	ft_putstr(str);
	len = (int)ft_strlen(str);
	free(str);
	return (len);
}

static int	vprintf(const char *fmt, va_list ap)
{
	size_t	i;
	int		status;
	int		len;

	len = 0;
	status = 0;
	i = 0;
	while (fmt[i] != '\0')
	{
		if (!status)
		{
			if (fmt[i] == '%')
				status = 1;
			else
			{
				ft_putchar(fmt[i]);
				len++;
			}
		}
		else
		{
			len += putconv(fmt[i], ap);
			status = 0;
		}
		i++;
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, fmt);
	res = vprintf(fmt, ap);
	va_end(ap);
	return (res);
}

// test function

int	main(void)
{
	int	a;

	ft_printf("%s\n", "lorem ipsum");
	ft_printf("I am %d%% sure!\n", 100);
	ft_printf("%c\n", 97);
	ft_printf("The address number of NULL is %p\n", &a);
	ft_printf("%x\n", 255);
	ft_printf("%X\n", 255);
	ft_printf("%s\n", 10);
	return (0);
}
