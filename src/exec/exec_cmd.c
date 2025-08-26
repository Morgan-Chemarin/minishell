/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:45:00 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child_command(t_cmd *cmd, t_env *env, t_all *all)
{
	char	*path;
	char	**envp_arr;

	g_last_status_exit = 0;
	if (cmd->type == CMD_BUILTNS)
	{
		exec_builtin(cmd, &env, all);
		free_all(all->cmd_head, all->token, env, all->line);
		exit(g_last_status_exit);
	}
	dot_command(cmd, env, all);
	envp_arr = env_list_to_array(env);
	path = get_path(cmd->args[0], env);
	if (path)
		check_access_exec(path, cmd->args, envp_arr);
	if (g_last_status_exit != 0)
	{
		free(path);
		free_split(envp_arr);
		free_all(all->cmd_head, all->token, all->env, all->line);
		exit(g_last_status_exit);
	}
	child_exit_handler(path, envp_arr, all);
}

void	execute_child_process(t_cmd *cmd, t_all *all, t_pipe_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(cmd, data->in_fd, data->pipe_fd);
	handle_redirections(cmd, all);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		if (cmd->args[0] && cmd->args[0][0] == '\0')
			child_exit_handler(NULL, NULL, all); // a revoir cette condition
		free_all(cmd, all->token, all->env, all->line);
		exit(EXIT_SUCCESS);
	}
	run_child_command(cmd, all->env, all);
}

int	handle_single_stateful(t_cmd *cmd, t_env **env, t_all *all)
{
	int	saved_fds[2];

	if (!(cmd->next == NULL && is_stateful_builtin(cmd)))
		return (0);
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	handle_redirections(cmd, all);
	exec_builtin(cmd, env, all);
	restore_fds(saved_fds);
	close(saved_fds[0]);
	close(saved_fds[1]);
	return (1);
}

void	exec_cmd(t_cmd *cmd, t_env **env, t_token *token, char *line)
{
	t_all	all;

	all.cmd_head = cmd;
	all.token = token;
	all.line = line;
	all.env = *env;
	if (cmd->next == NULL && cmd->type == CMD_BUILTNS
		&& ft_strcmp(cmd->args[0], "exit") == 0)
	{
		handle_redirections(cmd, &all);
		exec_builtin(cmd, &all.env, &all);
		*env = all.env;
		close_all_heredocs(cmd);
		return ;
	}
	if (handle_single_stateful(cmd, &all.env, &all))
	{
		*env = all.env;
		close_all_heredocs(cmd);
		return ;
	}
	exec_cmd_loop(cmd, &all.env, &all);
	*env = all.env;
}
