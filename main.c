int	ft_printf(const char *fmt, ...);

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
