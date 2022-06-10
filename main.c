#include "libftprintf.h"
#include <stdio.h>

int	main(void)
{
	ft_printf("%d\n", 123);
	return (0);
}

// int main(void)
// {
// 	int	a;
// 	ft_printf("hello world!\n");
// 	ft_printf("%s\n", "hello again!");
// 	ft_printf("The address number of a is %p\n", &a);
// 	// ft_printf("I am %d%% sure!\n", 100);
// 	ft_printf("%c\n", 97);
// 	// ft_printf("%x\n", 255);
// 	// ft_printf("%X\n", 255);
// 	// ft_printf("%s\n", 10);
// }

// #include <limits.h>

// int	main(void)
// {
// 	char		*str;
// 	int			n;
// 	t_convspec	*cs;

// 	n = INT_MAX;
// 	cs = calloc(1, sizeof(t_convspec));

// 	// printf("% 05.20d\n", n);
// 	// cs->specifier = 'd';
// 	// cs->precision = 20;
// 	// cs->width_min = 5;
// 	// cs->value = &n;
// 	// cs->flag_hash = 0;
// 	// cs->flag_zero = 1;
// 	// cs->flag_minus = 0;
// 	// cs->flag_space = 1;
// 	// cs->flag_plus = 0;
// 	// cs->flag_dot = 1;

// 	printf("%#20.10X\n", n);
// 	cs->specifier = 'X';
// 	cs->precision = 10;
// 	cs->width_min = 20;
// 	cs->value = &n;
// 	cs->flag_hash = 1;
// 	cs->flag_zero = 0;
// 	cs->flag_minus = 0;
// 	cs->flag_space = 1;
// 	cs->flag_plus = 0;
// 	cs->flag_dot = 1;

// 	expand_number(&str, cs);
// 	ft_putendl(str);
// 	free(str);
// 	return (0);
// }
