/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:38:17 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/16 22:32:05 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_access(char *path, char **args, char **envp)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			execve(path, args, envp);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
}

void	setup_child_pipes(t_cmd *cmd, int fds[3])
{
	if (fds[0] != 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (cmd->next)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

void	restore_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
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
