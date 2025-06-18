/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/06/18 16:12:27 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

// ajouter strndup / strcmp / printf

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next; 
}	t_env;

typedef enum e_cmd_type
{
	CMD_EXTERNAL,
	CMD_BUILTNS
}	t_cmd_type;

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
t_env			*new_env(void);

int				check_builtins_args(t_cmd *cmd);

void			exec_cmd(t_cmd *cmd);

// void	ft_putstr(char *str);
// int		ft_strcmp(char *s1, char *s2);
// void	echo(t_cmd *cmd);

#endif