/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input(char *file, t_all *all)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		free_all(all->cmd_head, all->token, all->env, all->line);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	handle_output(char *file, int append, t_all *all)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror(file);
		free_all(all->cmd_head, all->token, all->env, all->line);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_redirections(t_cmd *cmd, t_all *all)
{
	if (cmd->input_file)
		handle_input(cmd->input_file, all);
	if (cmd->output_file)
		handle_output(cmd->output_file, cmd->append, all);
}
