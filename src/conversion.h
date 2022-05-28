#ifndef CONVERSION_H
# define CONVERSION_H

// todo: field width and precision could be of size_t type

typedef struct s_convspec {
	char			specifier;
	unsigned int	precision;
	unsigned int	field_width;
	unsigned char	flag_hash: 1;
	unsigned char	flag_zero: 1;
	unsigned char	flag_minus: 1;
	unsigned char	flag_space: 1;
	unsigned char	flag_plus: 1;
	unsigned char	flag_period: 1;
}	t_convspec;

#endif
