NAME       = minishell

CC         = cc
CFLAGS     =  -Iinclude -Ilibft -Werror -Wextra -Wall
LDFLAGS    = -lreadline

SRC_DIR    = src
OBJ_DIR    = obj
LIBFT_DIR  = libft

SRCS = \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/builtins/cd/cd.c \
		$(SRC_DIR)/builtins/echo/echo.c \
		$(SRC_DIR)/builtins/exit/exit.c \
		$(SRC_DIR)/builtins/export/export.c \
		$(SRC_DIR)/builtins/export/env_export.c \
		$(SRC_DIR)/builtins/unset/unset.c \
		$(SRC_DIR)/builtins/pwd/pwd.c \
		$(SRC_DIR)/builtins/env/env.c \
		$(SRC_DIR)/env/init_env.c \
		$(SRC_DIR)/env/env_array.c \
		$(SRC_DIR)/env/env_expansion.c \
		$(SRC_DIR)/parser/split_quote.c \
		$(SRC_DIR)/parser/split_utils.c \
		$(SRC_DIR)/parser/split_quote_helper.c \
		$(SRC_DIR)/parser/token_builder.c \
		$(SRC_DIR)/parser/parsing.c \
		$(SRC_DIR)/exec/exec_cmd.c \
		$(SRC_DIR)/exec/pipe_cmd.c \
		$(SRC_DIR)/exec/heredoc.c \
		$(SRC_DIR)/exec/execve_utils.c \
		$(SRC_DIR)/utils/check_error.c \
		$(SRC_DIR)/utils/free_functions.c \

OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT      = $(LIBFT_DIR)/libft.a

all: $(OBJ_DIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re