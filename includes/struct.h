/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:36:53 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:22:08 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef enum e_redirection_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redir;
	t_cmd_type		type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_all
{
	t_cmd		*cmd_head;
	t_token		*token;
	t_env		*env;
	char		*line;
	int			heredoc_fd;
}	t_all;

typedef struct s_pipe_data
{
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;
}	t_pipe_data;

#endif