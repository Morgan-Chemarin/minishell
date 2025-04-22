/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:57 by dev               #+#    #+#             */
/*   Updated: 2025/04/22 13:49:38 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax_errors(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		//plein de if pour gerer si | | , > >, >> >
		// revoir condition PIPE quand pipe fait 
		if ((tmp->type == PIPE || tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
			&& (!tmp->next || tmp->next->type != WORD))
		{
			printf("Fichier manque apres '%s'\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
