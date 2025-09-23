/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:30:42 by dev               #+#    #+#             */
/*   Updated: 2025/09/23 16:29:32 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_in(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd < 0)
	{
		perror(r->file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_out(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(r->file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_append(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(r->file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static int	fd_from_fdpath(const char *path)
{
	char		*p;
	int			n;

	if (!path)
		return (-1);
	p = ft_strrchr(path, '/');
	if (!p || !*(p + 1))
		return (-1);
	n = ft_atoi(p + 1);
	if (n < 0)
		return (-1);
	return (n);
}

void	handle_hd(t_redirection *r)
{
	int	hd;

	hd = fd_from_fdpath(r->file);
	if (hd < 0)
	{
		if (!g_interrupted)
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
