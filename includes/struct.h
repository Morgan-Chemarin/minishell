/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:36:53 by dev               #+#    #+#             */
/*   Updated: 2025/08/21 14:08:06 by pibreiss         ###   ########.fr       */
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

typedef struct s_all
{
	t_cmd		*cmd_head;
	t_token		*token;
	t_env		*env;
	char		*line;
	int			heredoc_fd;
}	t_all;

typedef struct s_exec_data
{
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;
}	t_exec_data;

#endif