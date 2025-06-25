/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:14:36 by dev               #+#    #+#             */
/*   Updated: 2025/06/25 14:44:05 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

int	count_args(t_token *token)
{
	int	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
			token = token->next;
		token = token->next;
	}
	return (count);
}
