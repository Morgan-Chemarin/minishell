/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/08/12 17:30:00 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_pid_remastered(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_status_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status_exit = 128 + WTERMSIG(status);
}

int	is_stateful_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	return (!strcmp(cmd->args[0], "cd")
		|| !strcmp(cmd->args[0], "export")
		|| !strcmp(cmd->args[0], "unset")
		|| !strcmp(cmd->args[0], "exit"));
}

void	exec_builtin(t_cmd *cmd, t_env **env, t_token *token, char *line)
{
	if (!strcmp(cmd->args[0], "echo"))
		g_last_status_exit = ft_echo(cmd);
	else if (!strcmp(cmd->args[0], "cd"))
		g_last_status_exit = ft_cd(cmd, env);
	else if (!strcmp(cmd->args[0], "pwd"))
		g_last_status_exit = ft_pwd();
	else if (!strcmp(cmd->args[0], "export"))
		g_last_status_exit = ft_export(cmd, env);
	else if (!strcmp(cmd->args[0], "unset"))
		g_last_status_exit = ft_unset(env, cmd);
	else if (!strcmp(cmd->args[0], "env"))
		g_last_status_exit = ft_env(*env);
	else if (!strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, token, *env, line);
}

void exec_cmd(t_cmd *cmd, t_env *env, t_token *token, char *line)
{
	int		in_fd;
	int		pipe_fd[2];
	pid_t	pid;
	char	*path;
	char	**envp_arr;
	t_cmd	*cmd_head;

	in_fd = 0;
	path = NULL;
	envp_arr = NULL;
	cmd_head = cmd;
	while (cmd)
	{
		int heredoc_fd = -1;
		if (cmd->has_heredoc)
		{
			heredoc_fd = handle_heredoc(cmd, env);
			if (heredoc_fd < 0)
				return ;
		}

		int is_last = (cmd->next == NULL);
		int is_stateful = is_stateful_builtin(cmd);

		// Correction : ignorer si commande vide
        // if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
        // {
        //     ft_putstr_fd("minishell:jxv : command not found\n", 2);
        //     g_last_status_exit = 127;
        //     if (heredoc_fd != -1)
        //         close(heredoc_fd);
        //     cmd = cmd->next;
        //     continue;
        // }

		if (is_last && is_stateful)
		{
			int saved_stdin = dup(STDIN_FILENO);
			int saved_stdout = dup(STDOUT_FILENO);
			handle_redirections(cmd);
			if (heredoc_fd != -1)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
			exec_builtin(cmd, &env, token, line);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return;
		}
		if (cmd->next && pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return;
		}
		pid = fork();
		if (pid == 0)
		{
			// Fils
			//*PROBLEME GUILLEMENT SOIT "" SOIT REDIR
			// if (cmd->args[0] == NULL || cmd->args[0][0] == '\0')
			// {
			// 	ft_putstr_fd("minishell: dcknd: command not found\n", 2);
			// 	exit(127);
			// }
			if (in_fd != 0)
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
			handle_redirections(cmd);
			if (heredoc_fd != -1)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
			if (cmd->type == CMD_BUILTNS)
			{
				exec_builtin(cmd, &env, token, line);
				if (path)
					free(path);
				free_all(cmd_head, token, env, line);
				exit(g_last_status_exit);
			}
			if (ft_strcmp(cmd->args[0], ".") == 0)
			{
				if (!cmd->args[1])
				{
					ft_putstr_fd("minishell: .: filename argument required\n", 2);
					ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
					if (path)
						free(path);
					free_all(cmd, token, env, line);
					exit(2);
				}
			}
			envp_arr = env_list_to_array(env);
			if (!envp_arr)
			{
				free_all(cmd_head, token, env, line);
				exit(1);
			}
			if (ft_strchr(cmd->args[0], '/')) // si c'est un chemin direct
				check_access_exec(cmd->args[0], cmd->args, envp_arr);
			else // on cherche dans path
			{
				path = get_path(cmd->args[0], env);
				if (path) // si on trouve on execute
					check_access_exec(path, cmd->args, envp_arr);
				else // sinon on tente dans le dir actuel
					check_access_exec(cmd->args[0], cmd->args, envp_arr);
			}
			if (path)
        		free(path);
			free_all(cmd_head, token, env, line);
			exit(g_last_status_exit);
		}
		else if (pid < 0)
		{
			perror("fork");
			return;
		}
		// Parent
		wait_pid_remastered(pid);
		if (in_fd != 0)
			close(in_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			in_fd = pipe_fd[0];
		}
		if (heredoc_fd != -1)
			close(heredoc_fd);
		cmd = cmd->next;
	}
}
