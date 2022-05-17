char	*convert_char(char c)
{
	str = ft_strnew(2);
	if (str != NULL)
		*str = c;
	return (str);
}

char	*convert_str(t_convspec cs, char *src)
{
	size_t	len;

	if (cs->flag_precision)
		len = (size_t)cs->precision;
	else
		len = ft_strlen(src);
	return (ft_strndup(src, len));
}

char	*convert_addr(f_convspec cs, void *n)
{
	char	*nbr;

	nbr = ft_addrtoa(n);
	prependaltfl(&nbr);
	return (nbr);
}

char	*convert_int(f_convspec cs, int n)
{
	char	*nbr;
	size_t	nlen;

	nbr = ft_itoa(n);
	nlen = ft_strlen(nbr);
	if (cs->flag_precision && cs->precision > nlen)
		prependzeroes(&nbr, cs->precision - nlen);
	else if (!cs->flag_precision && !cs->flag_rpad && cs->flag_zero && cs->width_min > nlen)
		prependzeroes(&nbr, cs->width_min - nlen);
	if (n > 0)
		if (cs->flag_sign)
			prependplussign(&nbr);
		else if (cs->flag_space)
			prependspace(&nbr);
	return (nbr);
}

char	*convert_uint_dec(t_convspec cs, unsigned int n)
{
	char	*nbr;

	nbr = ft_uitoa(n);
	nlen = ft_strlen(nbr);
	if (cs->flag_precision && cs->precision > nlen)
		prependzeroes(&nbr, cs->precision - nlen);
	else if (!cs->flag_precision && !cs->flag_rpad && cs->flag_zero && cs->width_min > nlen)
		prependzeroes(&nbr, cs->width_min - nlen);
	return (nbr);
}

char	*convert(t_convspec cs, void *arg)
{
	char	*str;
	size_t	slen;

	if (cv->specifier == 'c')
		str = convert_char((int)*arg);
	else if (cv->specifier == 's')
		str = convert_str(cs, (char *)arg);
	else if (cv->specifier == 'p')
		str = convert_addr(cs, arg);
	else if (cv->specifier == 'd' || cv->specifier == 'i')
		str = convert_int(cs, (int)*arg);
	else if (cv->specifier == 'u')
		str = convert_uint_dec(cs, (unsigned int)*arg);
	else
		str = convert_uint_hex(cs, (unsigned int)*arg);
	if (str != NULL)
	{
		slen = ft_strlen(str);
		if (cs->width_min > slen)
			if (cs->flag_rpad)
				ft_appendspc(&str, cs->width_min - slen);
			else if (!cs->flag_zero || cs->flag_precision)
				ft_prependspc(&str, cs->width_min - slen);
	}
	return (str);
}

int	put_conversion(t_conv conv, void *arg)
{
	char	*str;
	size_t	slen;
	size_t	padding;
	char	c;

	if (conv->padding_type == CONV_PAD_TYP_ZERO)
		c = '0';
	else
		c = ' ';
	str = convert(conf, arg);
	slen = ft_strlen(str);
	padding = 0;
	if (conv->width_min > slen)
		padding = width_min - slen;
	if (padding > 0 && conv->padding == CONV_LEFT_PAD)
		ft_putnchars(c, padding);
	ft_putstr(str);
	free(str);
	if (padding > 0 && conv->padding == CONV_RIGHT_PAD)
		ft_putnchars(c, padding);
	return (padding + slen);
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

t_convspec	*str_to_convspec(char *str)
{
	t_convspec	*cs;

	cs = ft_calloc(1, sizeof(t_convspec));
	if (cs != NULL)
	{
		while (isflag(*str))
		{
			if (*str == '#')
				cs->flag_altf = 1;
			else if (*str == '+')
				cs->flag_sign = 1;
			else if (*str == '-')
				cs->flag_ljus = 1;
			else if (*str == '0')
				cs->flag_zero = 1;
			else if (*str == ' ')
				cs->flag_spac = 1;
			str++;
		}
		if (ft_isdigit(*str))
			cs->width_min = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		if (*str == '.')
			cs->flag_precision = 1;
		if (ft_isdigit(*str))
			cs->precision = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		if (isspecifier(*str))
			cs->specifier = *str;
	}
	return (cs);
}

char	*extract_convspecstr(char *str)
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
	if (!isspecifier)
		return (NULL);
	len++;
	return (ft_strndup(str, len));
}

static int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	int		cnt;
	char	*cstr;

	cnt = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			cstr = extract_convspec(fmt);
			if (cstr != NULL)
			{
				cnt += put_conversion(cstr, va_arg(ap, void *), fd);
				fmt += ft_strlen(cstr);
				free(cstr);
				continue ;
			}
			if (fmt[1] == '%')
				fmt++;
		}
		cnt += putchar(*fmt, fd);
		fmt++;
	}
	return (cnt);
}
