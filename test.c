#include "libft.h"
#include "conversion.h"
#include <stdlib.h>

int	convert_int(int (*wc)(int), t_convspec *cs, int n);

int	putchar(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	main(void)
{
    t_convspec  *cs;

	cs = calloc(1, sizeof(t_convspec));
    cs->field_width = 10;
    cs->specifier = 'd';
	convert_int(&putchar, cs, 42);
	return (0);

}
