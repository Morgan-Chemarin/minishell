/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:35:09 by dev               #+#    #+#             */
/*   Updated: 2025/09/29 18:49:54 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_heredocs(t_cmd *head)
{
	t_cmd			*cmd;
	t_redirection	*r;

	if (!head)
		return ;
	cmd = head;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == R_HEREDOC && r->file)
			{
				if (r->heredoc_fd >= 0)
					close(r->heredoc_fd);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}
