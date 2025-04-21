/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:38 by dev               #+#    #+#             */
/*   Updated: 2025/04/21 18:02:06 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

// typedef enum e_redir_type {
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	REDIR_HEREDOC
// }	t_redir_type;

// typedef struct s_redir {
// 	t_redir_type	type;
// 	char			*file;
// 	struct s_redir	*next;
// }	t_redir;

typedef struct s_cmd {
	char			**args;
	// t_redir			*redirs;
	// struct s_cmd	*next;
}	t_cmd;

# endif