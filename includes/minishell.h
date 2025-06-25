/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/06/25 02:48:50 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h> 

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
	t_cmd_type		type;
	struct s_cmd	*next;
}	t_cmd;

t_cmd			*parser(t_token *tokens);
int				check_syntax_errors(t_token *tokens);
t_token_type	get_token_type(char *s);
t_token			*create_struct_tokens(char **split);

char			*extract_word(char *line, int *i);
char			**split_with_quote(char *line);

t_cmd			*new_cmd(void);
int				count_args(t_token *token);

// banner.c
void			print_ascii_banner(void);

// init_env.c
t_env			*envp_to_list(char **envp);

int				check_builtins_args(t_cmd *cmd);

void    exec_cmd(t_cmd *cmd, t_env *env);

void	ft_putstr(char *str);
int		ft_strcmp(char *s1, char *s2);

void	ft_echo(t_cmd *cmd);
void	ft_env(t_env *envp);
void	ft_cd(t_cmd *cmd, t_env **env);
void	ft_exit(t_cmd *cmd);
void	ft_unset(t_env **env, t_cmd *cmd);
// void	ft_export(t_cmd *cmd, t_env **env);
void	ft_pwd(void);

#endif