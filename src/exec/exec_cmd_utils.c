/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:38:17 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/22 17:58:40 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command_in_loop(t_cmd *cmd, t_all *all, t_exec_data *data)
{
	if (cmd->has_heredoc)
		data->in_fd = handle_heredoc(cmd, all->env);
	if (cmd->next && pipe(data->pipe_fd) < 0)
	{
		perror("pipe");
		return ;
	}
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("fork");
		return ;
	}
	if (data->pid == 0)
		execute_child_process(cmd, all, data);
	if (data->in_fd != STDIN_FILENO)
		close(data->in_fd);
	if (cmd->next)
	{
		close(data->pipe_fd[1]);
		data->in_fd = data->pipe_fd[0];
	}
}

void	exec_cmd_loop(t_cmd *cmd, t_env **env, t_all *all)
{
	t_exec_data	data;

	data.in_fd = STDIN_FILENO;
	data.pid = -1;
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		all->env = *env;
		process_command_in_loop(cmd, all, &data);
		cmd = cmd->next;
	}
	wait_all_children(data.pid);
}

void	restore_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}
