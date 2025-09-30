/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:30:42 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 09:38:12 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd < 0)
	{
		perror(r->file);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	handle_out(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(r->file);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_append(t_redirection *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(r->file);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	handle_hd(t_redirection *r)
{
	int	hd;

	hd = r->heredoc_fd;
	if (dup2(hd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(hd);
		exit(1);
	}
	close(hd);
}
