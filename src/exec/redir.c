/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 09:38:32 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redirection	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == R_IN)
		{
			if (!handle_in(r))
				return (0);
		}
		else if (r->type == R_OUT)
		{
			if (!handle_out(r))
				return (0);
		}
		else if (r->type == R_APPEND)
		{
			if (!handle_append(r))
				return (0);
		}
		else if (r->type == R_HEREDOC)
			handle_hd(r);
		r = r->next;
	}
	return (1);
}
