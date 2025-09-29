/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:20:50 by dev               #+#    #+#             */
/*   Updated: 2025/09/29 19:09:19 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_interrupted(int sig)
{
	(void)sig;
	g_interrupted = 130;
	rl_cleanup_after_signal();
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
}

static int	prepare_heredocs_one_cmd(t_cmd *cmd, t_all *all)
{
	t_redirection	*r;
	int				fd;

	r = cmd->redir;
	while (r && !g_interrupted)
	{
		if (r->type == R_HEREDOC)
		{
			signal(SIGINT, set_heredoc_interrupted);
			fd = handle_heredoc(r->file, all);
			signal(SIGINT, siging_handler);
			if (fd < 0 || g_interrupted)
				return (0);
			r->heredoc_fd = fd;
		}
		r = r->next;
	}
	return (!g_interrupted);
}

int	prepare_all_heredocs(t_cmd *head, t_all *all)
{
	t_cmd	*c;

	g_interrupted = 0;
	c = head;
	while (c && !g_interrupted)
	{
		if (!prepare_heredocs_one_cmd(c, all))
			return (0);
		c = c->next;
	}
	return (!g_interrupted);
}
