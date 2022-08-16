#ifndef CONVERSION_H
# define CONVERSION_H
# define BASESET_DEC "0123456789"
# define BASESET_HEXL BASESET_DEC "abcdef"
# define BASESET_HEXU BASESET_DEC "ABCDEF"

// todo: field width and precision could be of size_t type

typedef struct s_conversion {
	char			specifier;
	int				precision;
	int				min_width;
	unsigned char	flag_hash: 1;
	unsigned char	flag_zero: 1;
	unsigned char	flag_minus: 1;
	unsigned char	flag_space: 1;
	unsigned char	flag_plus: 1;
	unsigned char	flag_period: 1;
}	t_conversion;

#endif
