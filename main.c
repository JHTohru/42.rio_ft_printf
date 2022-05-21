#include "libftprintf.h"

int	main(void)
{
	int	a;

	ft_printf("hello world!\n");
	ft_printf("%s\n", "hello again!");
	ft_printf("The address number of a is %p\n", &a);
	// ft_printf("I am %d%% sure!\n", 100);
	ft_printf("%c\n", 97);
	// ft_printf("%x\n", 255);
	// ft_printf("%X\n", 255);
	// ft_printf("%s\n", 10);
	return (0);
}
