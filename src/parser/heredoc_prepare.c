/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:20:50 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:37:56 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	prepare_heredocs_one_cmd(t_cmd *cmd, t_env *env)
{
	t_redirection	*r;
	int				fd;
	char			*path;

	r = cmd->redir;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			fd = handle_heredoc(r->file, env);
			if (fd < 0)
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
	return (1);
}

int	prepare_all_heredocs(t_cmd *head, t_env *env)
{
	t_cmd	*c;

	c = head;
	while (c)
	{
		if (!prepare_heredocs_one_cmd(c, env))
			return (0);
		c = c->next;
	}
	return (1);
}
