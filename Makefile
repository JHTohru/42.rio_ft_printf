CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := libft
LIBFT_LIB := libft.a
LIBFT := $(LIBFT_DIR)/$(LIBFT_LIB)

NAME := libftprintf.a
INC_DIR := inc
SRC_DIR := src
SRC_FILES := conversion_utils.c convert_char.c convert_hex.c convert_int.c \
	convert_ptr.c convert_str.c convert_uint.c ft_printf.c ft_printf2.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR := obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) ./
	@mv $(LIBFT_LIB) $@
	@ar -r $@ $(OBJS)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I $(LIBFT_DIR) -I $(INC_DIR) -I ./ -o $@ $<

clean:
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

BONUS_DIR := bonus
BONUS_INC_DIR := $(BONUS_DIR)/inc
BONUS_SRC_DIR := $(BONUS_DIR)/src
BONUS_SRC_FILES := conversion_utils_bonus.c convert_char_bonus.c convert_hex_bonus.c convert_int_bonus.c \
	convert_ptr_bonus.c convert_str_bonus.c convert_uint_bonus.c ft_printf_bonus.c ft_printf2_bonus.c
BONUS_SRCS := $(addprefix $(BONUS_SRC_DIR)/,$(BONUS_SRC_FILES))
BONUS_OBJS := $(BONUS_SRC_FILES:%.c=$(OBJ_DIR)/%.o)

bonus: $(LIBFT) $(BONUS_OBJS)
	cp $(LIBFT) ./
	mv $(LIBFT_LIB) $(NAME)
	ar -r $(NAME) $(BONUS_OBJS)

$(OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I $(LIBFT_DIR) -I $(BONUS_INC_DIR) -I ./ -o $@ $<

.PHONY: all, clean, fclean, re, bonus
