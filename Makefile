NAME       = minishell

CC         = cc 
CFLAGS     = -Wall -Wextra -Werror -MMD -MP -Iincludes -Ilibft -I gnl
LDFLAGS    = -lreadline

DIR_SRCS    =    src/builtins/cd \
                src/builtins/echo \
                src/builtins/exit \
                src/builtins/export \
                src/builtins/env \
                src/builtins/unset \
                src/builtins/pwd \
                src/env \
                src/parser \
                src/exec \
                src/utils \
                src/main

vpath %.c $(DIR_SRCS)
vpath %.h includes

SRC_DIR    = src
OBJ_DIR    = .obj
LIBFT_DIR  = libft

SRCS =     main.c \
        main_loop.c \
        cd.c \
        echo.c \
        exit.c \
        exit_utils.c \
        export.c \
        env_export.c \
        export_utils.c \
        unset.c \
        pwd.c \
        env.c \
        init_env.c \
        env_array.c \
        env_expansion.c \
        split_quote.c \
        split_utils.c \
        split_quote_helper.c \
        tokens_redir.c \
        tokens.c \
        parsing.c \
        exec_cmd.c \
        cmd_utils.c \
        heredoc.c \
        execve_utils.c \
        redir.c \
        wait_pid_remastered.c \
        exec_cmd_utils.c \
		exec_cmd_utils_children.c \
        exec_builtins.c\
        check_error.c \
        free_functions.c \

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS    = $(SRCS:%.c=$(OBJ_DIR)/%.d)

LIB_LIBFT      = $(LIBFT_DIR)/libft.a

all: lib $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIB_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_LIBFT) $(LDFLAGS) -o $@

lib:
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: lib all clean fclean re