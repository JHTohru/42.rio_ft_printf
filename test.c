#include <stdio.h>

int ft_printf(char *fmt, ...);

int assert_int_equals(int want, int got)
{
    if (got != want)
        fprintf(stderr, "wanted %d got %d\n", want, got);
    return (got == want);
}

int test_ft_printf(char *want, char *fmt, ...)
{}

int main(void)
{
    assert_int_equals(1, ft_printf("%c", 'x')); // "x"
	assert_int_equals(5, ft_printf("%5c", 'x')); // "x    "
	assert_int_equals(5, ft_printf("%-5c", 'x')); // "    x"
    assert_int_equals(8, ft_printf("%x", 3735928559)); // "deadbeef"
    assert_int_equals(10, ft_printf("%#x", 3735928559)); // "0xdeadbeef"
    assert_int_equals(13, ft_printf("%13x", 3735928559)); // "     deadbeef"
    assert_int_equals(13, ft_printf("%-13x", 3735928559)); // "deadbeef     "

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "   0xdeadbeef"
// 	write(1, "\n", 1);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "deadbeef     "
// 	write(1, "\n", 1);

// 	conv = new_conversion('x');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "0xdeadbeef   "
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 13;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 13;
//     conv->flag_hash = 1;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "0x000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0x00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "     00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "   0x00000deadbeef"
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000deadbeef     "
// 	write(1, "\n", 1);

//     conv = new_conversion('x');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0x00000deadbeef   "
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	convert_hex(conv, u); // "DEADBEEF"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('X');
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "0XDEADBEEF"
// 	write(1, "\n", 1);
// 	free(conv);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
// 	convert_hex(conv, u); // "     DEADBEEF"
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	convert_hex(conv, u); // "   0XDEADBEEF"
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "DEADBEEF     "
// 	write(1, "\n", 1);

// 	conv = new_conversion('X');
// 	conv->min_width = 13;
//     conv->flag_hash = 1;
// 	conv->flag_minus = 1;
// 	convert_hex(conv, u); // "0XDEADBEEF   "
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 13;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 13;
//     conv->flag_hash = 1;
//     conv->flag_zero = 1;
//     convert_hex(conv, u); // "0X000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0X00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "     00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "   0X00000DEADBEEF"
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "00000DEADBEEF     "
// 	write(1, "\n", 1);

//     conv = new_conversion('X');
//     conv->min_width = 18;
//     conv->flag_minus = 1;
//     conv->flag_hash = 1;
//     conv->flag_period = 1;
//     conv->precision = 13;
//     convert_hex(conv, u); // "0X00000DEADBEEF   "
// 	write(1, "\n", 1);

// 	return (0);
// }

	return (0);
}
