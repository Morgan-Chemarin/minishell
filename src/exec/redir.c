/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:17:04 by dev               #+#    #+#             */
/*   Updated: 2025/07/17 18:21:08 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror(file);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	handle_output(char *file, int append)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT
			| (append ? O_APPEND : O_TRUNC), 0644);
	if (fd < 0)
		perror(file);
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_redirections(t_cmd *cmd)
{
	if (cmd->input_file)
		handle_input(cmd->input_file);
	if (cmd->output_file)
		handle_output(cmd->output_file, cmd->append);
}
