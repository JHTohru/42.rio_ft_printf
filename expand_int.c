#include <stdlib.h>
#include <stdio.h>

typedef struct s_convspec {
	char			specifier;
	int				precision;
	int				width_min;
	void			*value;
	unsigned char	flag_hash: 1;
	unsigned char	flag_zero: 1;
	unsigned char	flag_minus: 1;
	unsigned char	flag_space: 1;
	unsigned char	flag_plus: 1;
	unsigned char	flag_dot: 1;
}	t_convspec;

unsigned int	ft_upow(unsigned int b, unsigned int e)
{
	int	i;
	int	n;

	n = 1;
	i = 0;
	while (e > 0)
	{
		n *= b;
		e--;
	}
	return (n);
}

// int
int	expand(char **str, t_convspec *cs)
{
	int				padding_left;
	int				padding_right;
	int				leading_zeros;
	int				flag_zero;
	int				n_is_negative;
	unsigned int	n;
	unsigned int	m;
	int				nlen;
	unsigned int	magnitude;
	int				len;
	int				i;
	int				j;

	n_is_negative = *((int *)cs->value) < 0;
	if (n_is_negative)
		n = *((int *)cs->value) * -1;
	else
		n = *((int *)cs->value);
	nlen = 0;
	m = n;
	while(1)
	{
		nlen++;
		m /= 10;
		if (m == 0)
			break ;
	}
	magnitude = ft_upow(10, nlen - 1);
	// printf("1st nlen = %d\n", nlen);
	leading_zeros = 0;
	if (cs->flag_dot && cs->precision > nlen)
		leading_zeros = cs->precision - nlen;
	padding_left = 0;
	if (n_is_negative|| cs->flag_plus)
		nlen++;
	else if (cs->flag_space)
		padding_left++;
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
		if (n_is_negative)
			(*str)[i++] = '-';
		else if (cs->flag_plus)
			(*str)[i++] = '+';
		j = 0;
		while (j < leading_zeros)
			(*str)[i + j++] = '0';
		i += j;
		m = n;
		// printf("\n####################\n\n");
		while (1)
		{
			// printf("i = %d\n", i);
			// printf("m = %d\n", m);
			// printf("magnitude = %d\n", magnitude);
			// printf("c = %c\n", m / magnitude + '0');
			// printf("\n--------------------\n\n");
			(*str)[i++] = m / magnitude + '0';
			m %= magnitude;
			magnitude /= 10;
			if (magnitude == 0)
				break ;
		}
		// printf("\n####################\n\n");
		j = 0;
		while (j < padding_right)
			(*str)[i + j++] = ' ';
		(*str)[i + j] = '\0'; // desnecessário se str for alocado com calloc
		if (i + j != len)
		{
			printf("oh no!\n");
			printf("i = %d\nj = %d\nlen = %d\n", i, j, len);
		}
	}
	return (nlen);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putendl(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

#include <limits.h>

int	main(void)
{
	char		*str;
	int			n;
	t_convspec	*cs;

	n = INT_MAX;
	printf("% 05.20d\n", n);
	cs = calloc(1, sizeof(t_convspec));
	cs->specifier = 'd';
	cs->precision = 20;
	cs->width_min = 5;
	cs->value = &n;
	cs->flag_hash = 0;
	cs->flag_zero = 1;
	cs->flag_minus = 0;
	cs->flag_space = 1;
	cs->flag_plus = 0;
	cs->flag_dot = 1;
	expand(&str, cs);
	ft_putendl(str);
	free(str);
	return (0);
}
