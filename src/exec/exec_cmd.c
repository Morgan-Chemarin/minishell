/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/08/19 11:18:12 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_child_command(t_cmd *cmd, t_env *env, t_all *all)
{
	char	*path;
	char	**envp_arr;

	if (cmd->type == CMD_BUILTNS)
	{
		exec_builtin(cmd, &env, all);
		free_all(all->cmd_head, all->token, env, all->line);
		exit(g_last_status_exit);
	}
	dot_command(cmd, env, all);
	envp_arr = env_list_to_array(env);
	if (ft_strchr(cmd->args[0], '/'))
		check_access_exec(cmd->args[0], cmd->args, envp_arr);
	path = get_path(cmd->args[0], env);
	if (path)
		check_access_exec(path, cmd->args, envp_arr);
	child_exit_handler(path, envp_arr, all);
}

void	execute_child_process(t_cmd *cmd, t_env *env, t_all *all, int fds[3])
{
	char	*path;
	char	**envp_arr;

	path = NULL;
	all->env = env;
	setup_child_pipes(cmd, fds);
	handle_redirections(cmd);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		if (cmd->args[0] && cmd->args[0][0] == '\0')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		exit(EXIT_SUCCESS);
	}
	if (fds[2] != -1)
	{
		dup2(fds[2], STDIN_FILENO);
		close(fds[2]);
	}
	run_child_command(cmd, env, all);
}

void	execute_parent_process(pid_t pid, t_cmd *cmd, int fds[3])
{
	wait_pid_remastered(pid);
	if (fds[0] != 0)
		close(fds[0]);
	if (cmd->next)
	{
		close(fds[1]);
		fds[0] = fds[1];
	}
	else
		fds[0] = 0;
	if (fds[2] != -1)
		close(fds[2]);
}

int	handle_single_stateful(t_cmd *cmd, t_env **env, t_all *all)
{
	int	saved_fds[2];

	if (!(cmd->next == NULL && is_stateful_builtin(cmd)))
		return (0);
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	if (cmd->has_heredoc)
	{
		all->heredoc_fd = handle_heredoc(cmd, *env);
		if (all->heredoc_fd < 0)
			return (restore_fds(saved_fds), 1);
		dup2(all->heredoc_fd, STDIN_FILENO);
		close(all->heredoc_fd);
	}
	exec_builtin(cmd, env, all);
	restore_fds(saved_fds);
	return (1);
}

void	exec_cmd(t_cmd *cmd, t_env *env, t_token *token, char *line)
{
	t_all	all;

	all.cmd_head = cmd;
	all.token = token;
	all.line = line;
	all.env = env;
	if (handle_single_stateful(cmd, &env, &all))
		return ;
	exec_cmd_loop(cmd, &env, &all);
}
