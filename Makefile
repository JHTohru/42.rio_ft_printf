CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := libftprintf.a
LIBFT := libft.a
LIBFT_DIR := ./libft
SRC := ./src
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@mv $(LIBFT) $@
	ar -r $@ $(OBJS)

$(LIBFT):
	@echo "building libft"
	@make all clean -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/$(LIBFT) .

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c -o $@ $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
