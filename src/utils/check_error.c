/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:57 by dev               #+#    #+#             */
/*   Updated: 2025/07/24 09:05:51 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//plein de if pour gerer si | | , > >, >> >
// revoir condition PIPE quand pipe fait 

int	check_syntax_errors(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->type == PIPE || tmp->type == REDIR_IN
				|| tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			&& (!tmp->next || tmp->next->type != WORD))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
