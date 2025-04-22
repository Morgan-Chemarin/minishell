NAME       = minishell

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -Iinclude -Ilibft
LDFLAGS    = -lreadline

SRC_DIR    = src
OBJ_DIR    = obj
LIBFT_DIR  = libft

SRCS       = $(wildcard $(SRC_DIR)/*.c)
OBJS       = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT      = $(LIBFT_DIR)/libft.a

all: $(OBJ_DIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
