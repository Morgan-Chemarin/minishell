/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/06/26 22:34:51 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int is_stateful_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 0;
	return (!strcmp(cmd->args[0], "cd")
		|| !strcmp(cmd->args[0], "export")
		|| !strcmp(cmd->args[0], "unset")
		|| !strcmp(cmd->args[0], "exit"));
}

void handle_redirections(t_cmd *cmd)
{
	int fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
			perror(cmd->input_file);
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	if (cmd->output_file)
	{
		if (cmd->append)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(cmd->output_file);
		else
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

void exec_builtin(t_cmd *cmd, t_env **env)
{
	if (!strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, env);
	else if (!strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (!strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (!strcmp(cmd->args[0], "unset"))
		ft_unset(env, cmd);
	else if (!strcmp(cmd->args[0], "env"))
		ft_env(*env);
	else if (!strcmp(cmd->args[0], "exit"))
		ft_exit(cmd);
}


void exec_cmd(t_cmd *cmd, t_env *env)
{
	int		in_fd = 0;
	int		pipe_fd[2];
	pid_t	pid;

	while (cmd)
	{
		int is_last = (cmd->next == NULL);
		int is_stateful = is_stateful_builtin(cmd);

		// Cas 1 : built-in stateful, sans pipe
		if (is_last && is_stateful)
		{
			int saved_stdin = dup(STDIN_FILENO);
			int saved_stdout = dup(STDOUT_FILENO);
			handle_redirections(cmd);
			exec_builtin(cmd, &env);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return;
		}

		// Sinon, gestion avec pipe + fork
		if (cmd->next && pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return;
		}

		pid = fork();
		if (pid == 0)
		{
			// Child
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
			if (cmd->type == CMD_BUILTNS)
			{
				exec_builtin(cmd, &env);
				exit(0); // quitte sans execvp
			}
			execvp(cmd->args[0], cmd->args);
			perror("execvp");
			exit(127);
		}
		else if (pid < 0)
		{
			perror("fork");
			return;
		}

		// Parent
		waitpid(pid, NULL, 0);
		if (in_fd != 0)
			close(in_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			in_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
}












// void exec_cmd(t_cmd *cmd, t_env *env)
// {
// 	int		in_fd;
// 	int		pipe_fd[2];
// 	pid_t	pid;

// 	in_fd = 0;
// 	if (!cmd->next && is_stateful_builtin(cmd))
// 	{
// 		handle_redirections(cmd);
// 		exec_builtin(cmd, &env);
// 		return;
// 	}
// 	while (cmd)
// 	{
// 		if (cmd->next && pipe(pipe_fd) < 0)
// 		{
// 			perror("pipe");
// 			return;
// 		}
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (in_fd != 0)
// 			{
// 				dup2(in_fd, STDIN_FILENO);
// 				close(in_fd);
// 			}
// 			if (cmd->next)
// 			{
// 				close(pipe_fd[0]);
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 				close(pipe_fd[1]);
// 			}
// 			handle_redirections(cmd);
// 			if (cmd->type == CMD_BUILTNS)
// 			{
// 				exec_builtin(cmd, &env);
// 				exit(0);
// 			}
// 			execvp(cmd->args[0], cmd->args); // rajouter list to char pour execvp
// 			perror("execvp");
// 			exit(127);
// 		}
// 		else if (pid < 0)
// 		{
// 			perror("fork");
// 			return;
// 		}
// 		waitpid(pid, NULL, 0);
// 		if (in_fd != 0)
// 			close(in_fd);
// 		if (cmd->next)
// 		{
// 			close(pipe_fd[1]);
// 			in_fd = pipe_fd[0];
// 		}
// 		cmd = cmd->next;
// 	}
// }
