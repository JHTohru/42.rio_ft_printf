#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#define BASESET_DEC "0123456789"
#define BASESET_HEXL (BASESET_DEC "abcdef")
#define BASESET_HEXU (BASESET_DEC "ABCDEF")

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

unsigned int	upow(unsigned int b, unsigned int e)
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
	magnitude = upow(raddix, nlen - 1);
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
			printf("radd    ix = %d\n", raddix);

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
	return (len);
}

// A conversion with a field width greater than its number length must be padded
// with left spaces (by default).

int	test_int_min_width() // %10d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = -12345;
	expected_str = "    -12345";
	cs = calloc(1, sizeof(t_convspec));
    cs->width_min = 10;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_min_width: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

// If the result of a conversion is wider than the field width, there will be
// no modification since there is no case that a nonexistent or small field
// width cause truncation of a field.

int	test_int_min_width2() // %5d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
    cs->width_min = 5;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_min_width2: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

int	test_int_min_width3() // %3d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
    cs->width_min = 3;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_min_width3: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

// If the flag - is specified, the result of the conversion is left-justified
// within the field.

int	test_int_flag_minus() // %-10d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = -12345;
	expected_str = "-12345    ";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_minus = 1;
    cs->width_min = 10;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_flag_minus: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

// If the result of a conversion is wider than the field width, there will be
// no modification since there is no case that a nonexistent or small field
// width cause truncation of a field.

int	test_int_flag_minus2() // %-5d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_minus = 1;
    cs->width_min = 5;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_flag_minus2: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

int	test_int_flag_minus3() // %-3d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_minus = 1;
    cs->width_min = 3;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_flag_minus3: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

// If the flag 0 is specified for d, i, o, u, x, X, a, A, e, E, f, F, g, and G
// conversions, leading zeros (following any indication of sign or base) are
// used to pad to the field width rather than performing space padding, except
// when converting an infinity or NaN.

int	test_int_flag_zero() // %010d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = -12345;
	expected_str = "-000012345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_zero = 1;
    cs->width_min = 10;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_flag_zero: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

// If the specified field width value is not greater the length of the
// resulting conversion, a zero flag will take no effect.

int	test_int_small_width_flag_zero() // %05d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_zero = 1;
    cs->width_min = 5;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_small_wdith_flag_zero: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}

int	test_int_small_width_flag_zero2() // %03d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = 12345;
	expected_str = "12345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_zero = 1;
    cs->width_min = 3;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_small_wdith_flag_zero2: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}
int	test_int_flag_zero3() // %03d
{
    t_convspec  *cs;
	char		*str;
    char        *expected_str;
	int			d;
	int			res;
	int			ret;

	d = -12345;
	expected_str = "-12345";
	cs = calloc(1, sizeof(t_convspec));
	cs->flag_zero = 1;
    cs->width_min = 3;
    cs->specifier = 'd';
    ret = convert_number(&str, cs, d);
	res = strcmp(str, expected_str) == 0 && (size_t)ret == strlen(expected_str);
	printf("test_int_flag_zero3: ");
	if (res)
		printf("OK!\n");
	else
		printf("KO!\n");
    free(str);
	return (res);
}


int main(void)
{	
	test_int_min_width();
	test_int_min_width2();
	test_int_min_width3();
	test_int_flag_minus();
	test_int_flag_minus2();
	test_int_flag_minus3();
	test_int_flag_zero();
	test_int_flag_zero2();
	test_int_flag_zero3();
    return (0);
}
