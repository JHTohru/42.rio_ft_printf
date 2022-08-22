CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := libftprintf.a
INC_DIR := inc
LIBFT_DIR := libft
LIBFT_FILE := libft.a
LIBFT := $(LIBFT_DIR)/$(LIBFT_FILE)
SRC_DIR := src
SRC_FILES := conversion_utils.c convert_char.c convert_hex.c convert_int.c \
	convert_ptr.c convert_str.c convert_uint.c ft_printf.c ft_printf2.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR := obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

foo:
	echo $(SRCS)

$(NAME): $(LIBFT) $(OBJS)
	@mv $(LIBFT) $@
	@ar -r $@ $(OBJS)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ $<

clean:
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
