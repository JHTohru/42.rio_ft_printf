CC := cc
CFLAGS := -Wno-format
NAME := test
BIN_DIR := bin
PRINTF_DIR := ..
BONUS_DIR := $(PRINTF_DIR)/bonus
PRINTF_FILE := libftprintf.a
PRINTF_LIB := $(PRINTF_DIR)/$(PRINTF_FILE)
SRC_DIR := src
SRC_FILES := test.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

all: $(NAME)

$(NAME): $(SRCS) $(PRINTF_LIB)
	@$(CC) $(CFLAGS) -I $(PRINTF_DIR) -o $@ $^ -ldl

$(PRINTF_LIB):
	@make all -C $(PRINTF_DIR)
	@#make bonus -C $(PRINTF_DIR)

clean:
	@rm -f $(NAME)

fclean: clean
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all, clean, fclean, re
