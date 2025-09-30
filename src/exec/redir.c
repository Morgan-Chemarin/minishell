/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 18:46:54 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_single_redirection(t_redirection *r)
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
	{
		if (!handle_hd(r))
			return (0);
	}
	return (1);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redirection	*r;

	r = cmd->redir;
	while (r)
	{
		if (!process_single_redirection(r))
			return (0);
		r = r->next;
	}
	return (1);
}
