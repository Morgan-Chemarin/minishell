/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/07/17 18:21:31 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <sys/ioctl.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define RESET       "\001\033[0m\002"
# define RED         "\001\033[1;31m\002"
# define GREEN       "\001\033[1;32m\002"
# define YELLOW      "\001\033[1;33m\002"
# define BLUE        "\001\033[1;34m\002"
# define MAGENTA     "\001\033[1;35m\002"
# define CYAN        "\001\033[1;36m\002"
# define WHITE       "\001\033[0;37m\002"

// ajouter strndup / strcmp / printf

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_cmd_type
{
	CMD_EXTERNAL,
	CMD_BUILTNS
}	t_cmd_type;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append;
	int				has_heredoc;
	char			*heredoc_delim;
	t_cmd_type		type;
	struct s_cmd	*next;
}	t_cmd;

extern int	g_last_status_exit;

// ** BUILTINS **

int		ft_echo(t_cmd *cmd);
int		ft_env(t_env *envp);
int		ft_cd(t_cmd *cmd, t_env **env);
void	ft_exit(t_cmd *cmd, t_token *token, t_env *env, char *line);
int		ft_unset(t_env **env, t_cmd *cmd);
int		ft_pwd(void);

// export
void	ft_env_export(t_env *envp);
int		ft_export(t_cmd *cmd, t_env **env);

// utils_builtins
int		count_arg(char **arg);

// ** ENV **

// env_expansion.c
char	*expand_variables(char *str, t_env *env);
char	*get_env_value(char *name, t_env *env);

// init_env.c
t_env	*envp_to_list(char **envp);

// env_array.c
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
char	**env_list_to_array(t_env *env);
void	ft_free_split(char **arr);

// ** EXEC **

// exec_cmd.c
void	exec_cmd(t_cmd *cmd, t_env *env, t_token *token, char *line);

// pipe_cmd.c
t_cmd	*new_cmd(void);
int		count_args(t_token *token);

// heredoc.c
int		handle_heredoc(t_cmd *cmd, t_env *env);

// execve_utils.c
char	*get_path(char *cmd, t_env *env);
void	check_access_exec(char *cmd, char **args, char **envp);

// redir.c
void	handle_redirections(t_cmd *cmd);

// ** PARSER **

// parsing.c
t_cmd	*parser(t_token *tokens);
t_token	*create_struct_tokens(char **split);

// split_quote.c
char	**split_with_quote(char *line, t_env *env);
char	*extract_word(char *line, int *i, t_env *env, int skip_expand);

// split_quote_helper.c
char	*extract_quoted(char *line, int *i, int skip_expand, t_env *env);
int		count_tokens(char *line);

// split_utils.c
void	skip_spaces(char *line, int *i);
int		is_single_operator(char c);
int		is_double_operator(char *s, const char *op, int *i);
char	*extract_delimiter(char *line, int *i);

// token_builder.c

// ** UTILS **

// check_error.c
int		check_syntax_errors(t_token *tokens);

//free_utils
void	free_array_str(char	**str);
void	free_cmd(t_cmd *cmd);
void	free_token(t_token *token);
void	free_env(t_env *env);

#endif