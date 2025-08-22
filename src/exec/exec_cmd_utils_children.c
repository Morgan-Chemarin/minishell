/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils_children.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:14:17 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_children(pid_t last_pid)
{
	int	status;

	if (last_pid <= 0)
		return ;
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		g_last_status_exit = 128 + WTERMSIG(status);
	}
	else
		g_last_status_exit = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
	signal(SIGINT, siging_handler);
}

void	setup_child_pipes(t_cmd *cmd, int in_fd, int pipe_fd[2])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	child_exit_handler(char *path, char **envp_arr, t_all *all)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(all->cmd_head->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (path)
		free(path);
	if (envp_arr)
		free_split(envp_arr);
	free_all(all->cmd_head, all->token, all->env, all->line);
	exit(127);
}
