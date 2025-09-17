/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/09/17 20:32:59 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_cmd *cmd, t_all *all)
{
	t_redirection	*r;

	(void)all;
	r = cmd->redir;
	while (r)
	{
		if (r->type == R_IN)
			handle_in(r);
		else if (r->type == R_OUT)
			handle_out(r);
		else if (r->type == R_APPEND)
			handle_append(r);
		else if (r->type == R_HEREDOC)
			handle_hd(r);
		r = r->next;
	}
}
