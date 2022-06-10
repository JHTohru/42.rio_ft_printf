#include "libft.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	write_chars(char *str, int c, int n)
{
	ft_memset((void *)str, c, (size_t)n);
	return (n);
}

unsigned int	upow(unsigned int b, unsigned int e)
{
	unsigned int	p;

	p = 1;
	while (e != 0)
	{
		p *= b;
		e--;
	}
	return (p);
}

unsigned int	ulog(unsigned int n, unsigned int b)
{
	unsigned int	lg;

	lg = 0;
	while (n > b)
	{
		n /= b;
		lg++;
	}
	return(lg);
}

int	uwrite(char *str, unsigned int n, char *baseset)
{
	unsigned int	mag;
	unsigned int	rad;
	int		i;

	i = 0;
	rad = (unsigned int)ft_strlen(baseset);
	mag = upow(rad, ulog(n, rad));
	while (1)
	{
		str[i++] = baseset[n / mag];
		n %= mag;
		mag /= rad;
		if (mag == 0)
			break ;
	}
	return (i);
}

int	udigits(unsigned int n, int r) // esse nome não é muito bom.
{
	int	cnt;

	cnt = 0;
	while (1)
	{
		cnt++;
		n /= (unsigned int)r;
		if (n == 0)
			return (cnt);
	}
}
