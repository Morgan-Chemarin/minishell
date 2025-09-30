/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 18:40:55 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child_command(t_cmd *cmd, t_all *all)
{
	char	*path;
	char	**envp_arr;

	all->last_status_exit = 0;
	if (cmd->type == CMD_BUILTNS)
	{
		exec_builtin(cmd, all);
		free_all(all);
		exit(all->last_status_exit);
	}
	dot_command(cmd, all);
	envp_arr = env_list_to_array(all->env);
	path = get_path(cmd->args[0], all->env);
	if (path)
		check_access_exec(path, cmd->args, envp_arr, all);
	if (all->last_status_exit != 0)
	{
		free(path);
		free_split(envp_arr);
		free_all(all);
		exit(all->last_status_exit);
	}
	child_exit_handler(cmd, path, envp_arr, all);
}

void	execute_child_process(t_cmd *cmd, t_all *all, t_pipe_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(cmd, data->in_fd, data->pipe_fd);
	handle_redirections(cmd);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		if (cmd->args[0] && cmd->args[0][0] == '\0')
			child_exit_handler(cmd, NULL, NULL, all);
		free_all(all);
		exit(EXIT_SUCCESS);
	}
	run_child_command(cmd, all);
}

int	handle_single_stateful(t_cmd *cmd, t_all *all)
{
	if (!(cmd->next == NULL && is_stateful_builtin(cmd)))
		return (0);
	all->saved_fds[0] = dup(STDIN_FILENO);
	all->saved_fds[1] = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	exec_builtin(cmd, all);
	restore_fds(all->saved_fds);
	close(all->saved_fds[0]);
	close(all->saved_fds[1]);
	return (1);
}

void	exec_cmd(t_cmd *cmd, t_all *all)
{
	if (!cmd)
		return ;
	if (handle_single_stateful(cmd, all))
		return ;
	save_fds(all->saved_fds);
	if (!handle_redirections(cmd))
	{
		all->last_status_exit = 1;
		restore_fds(all->saved_fds);
		close(all->saved_fds[0]);
		close(all->saved_fds[1]);
		close_all_heredocs(cmd);
		return ;
	}
	exec_cmd_loop(cmd, all);
	restore_fds(all->saved_fds);
}
