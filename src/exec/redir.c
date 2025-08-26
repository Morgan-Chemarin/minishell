/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:44:18 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fd_from_fdpath(const char *path)
{
	const char	*p;
	int			n;

	if (!path)
		return (-1);
	p = strrchr(path, '/');
	if (!p || !*(p + 1))
		return (-1);
	n = atoi(p + 1); // vrai atoi lautre me casse les couilles
	if (n < 0)
		return (-1);
	return (n);
}

void	handle_redirections(t_cmd *cmd, t_all *all)
{
	t_redirection	*r;
	int				fd;
	int				hd;

	r = cmd->redir;
	(void)all;
	while (r)
	{
		if (r->type == R_IN)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
			{
				perror(r->file);
				//free ?
				exit(1); // pas sur 
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == R_OUT)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(r->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == R_APPEND)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(r->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == R_HEREDOC)
		{
			hd = fd_from_fdpath(r->file);
			if (hd < 0)
			{
				fprintf(stderr, "bad heredoc fd path: %s\n", r->file);
				exit(1);
			}
			if (dup2(hd, STDIN_FILENO) < 0)
			{
				perror("dup2");
				close(hd);
				exit(1);
			}
			close(hd);
		}
		r = r->next;
	}
}
