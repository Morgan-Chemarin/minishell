/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:35:09 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:30:03 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_fd_from_path(const char *path)
{
	if (!path)
		return (-1);
	if (strncmp(path, "/dev/fd/", 8) != 0) // vrai atoi et strncpm
		return (-1);
	return (atoi(path + 8));
}

void	close_all_heredocs(t_cmd *head)
{
	t_cmd			*cmd;
	t_redirection	*r;
	int				fd;

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
				fd = extract_fd_from_path(r->file);
				if (fd >= 0)
					close(fd);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}
