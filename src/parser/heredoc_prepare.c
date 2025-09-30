/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:20:50 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 10:01:02 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_interrupt_hook(void)
{
    if (g_interrupted)
    {
        rl_done = 1;
        return 0;
    }
    return 0;
}

void	set_heredoc_interrupted(int sig)
{
	(void)sig;
	g_interrupted = 130;
	write(STDOUT_FILENO, "\n", 1); // ptetre de trop aussi
	rl_done = 1; // ptetre
}

static int	prepare_heredocs_one_cmd(t_cmd *cmd, t_all *all)
{
	t_redirection	*r;
	int				fd;
	rl_hook_func_t *old_hook;

	r = cmd->redir;
	while (r && !g_interrupted)
	{
		if (r->type == R_HEREDOC)
		{
			old_hook = rl_event_hook;
			rl_event_hook = check_interrupt_hook;
			
			signal(SIGINT, set_heredoc_interrupted);
			fd = handle_heredoc(r->file, all);
			
			rl_event_hook = old_hook;
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
