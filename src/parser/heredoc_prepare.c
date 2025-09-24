/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:20:50 by dev               #+#    #+#             */
/*   Updated: 2025/09/24 12:26:36 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_heredoc_interrupted(int sig)
{
    (void)sig;
    g_interrupted = 130;
    rl_cleanup_after_signal();
    write(STDOUT_FILENO, "\n", 1);
    rl_done = 1;
}

static char	*make_fd_path(int fd)
{
	char	*num;
	char	*path;
	char	*tmp;

	num = ft_itoa(fd);
	if (!num)
		return (NULL);
	tmp = ft_strjoin("/dev/fd/", num);
	free(num);
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp);
	free(tmp);
	return (path);
}

static int	prepare_heredocs_one_cmd(t_cmd *cmd, t_env *env, t_all *all)
{
	t_redirection	*r;
	int				fd;
	char			*path;

	r = cmd->redir;
	while (r && !g_interrupted)
	{
		if (r->type == R_HEREDOC)
		{
			signal(SIGINT, set_heredoc_interrupted);
			fd = handle_heredoc(r->file, env, all);
			signal(SIGINT, siging_handler);
			if (fd < 0 || g_interrupted)
				return (0);
			path = make_fd_path(fd);
			if (!path)
			{
				close(fd);
				return (0);
			}
			free(r->file);
			r->file = path;
		}
		r = r->next;
	}
	return (!g_interrupted);
}

int	prepare_all_heredocs(t_cmd *head, t_env *env, t_all *all)
{
	t_cmd	*c;

	g_interrupted = 0;
	c = head;
	while (c && !g_interrupted)
	{
		if (!prepare_heredocs_one_cmd(c, env, all))
			return (0);
		c = c->next;
	}
	return (!g_interrupted);
}
