CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := libft.a
SRCS := ft_abs.c ft_atoi.c ft_isdigit.c ft_isspace.c ft_ptoa_base.c \
	ft_putchar_fd.c ft_putchar.c ft_putnchars_fd.c ft_putnchars.c \
	ft_putnstr_fd.c ft_putnstr.c ft_putstr_fd.c ft_putstr.c ft_strlen.c \
	ft_strnlen.c ft_utoa_base.c
OBJS := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
