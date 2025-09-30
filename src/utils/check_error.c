/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:57 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 18:59:00 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_errors(t_token *tmp, t_token *prev)
{
	if (tmp->type == PIPE && (!prev || (prev->type != WORD
				&& prev->type != REDIR_IN && prev->type != REDIR_OUT
				&& prev->type != REDIR_APPEND
				&& prev->type != REDIR_HEREDOC)))
	{
		printf("syntax error near unexpected token '%s'\n", tmp->value);
		return (0);
	}
	if (tmp->type == PIPE && !tmp->next)
	{
		printf("syntax error near unexpected token '%s'\n", tmp->value);
		return (0);
	}
	return (1);
}

int	check_syntax_errors(t_token *tokens)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = tokens;
	prev = NULL;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			&& (!tmp->next || tmp->next->type != WORD))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->value);
			return (0);
		}
		if (!check_pipe_errors(tmp, prev))
			return (0);
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}
