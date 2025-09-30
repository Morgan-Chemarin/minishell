/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:29 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/30 18:39:42 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	free_all(t_all *all)
{
	if (all->cmd_head)
		free_cmd(all->cmd_head);
	if (all->env)
		free_env(all->env);
	if (all->token)
		free_token(all->token);
	if (all->line)
		free(all->line);
	if (all->saved_fds[0])
		close(all->saved_fds[0]);
	if (all->saved_fds[1])
		close(all->saved_fds[1]);
	rl_clear_history();
}

int	print_exit_msg(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd >= 0)
		write(tty_fd, "exit\n", 5);
	else
		write(STDOUT_FILENO, "exit\n", 5);
	return (tty_fd);
}

void	exit_with_code(t_cmd *cmd, t_all *all, int tty_fd)
{
	int	code;

	if (!is_valid_long_long(cmd->args[1]))
	{
		write(tty_fd, "minishell: exit: ", 17);
		write(tty_fd, cmd->args[1], ft_strlen(cmd->args[1]));
		write(tty_fd, ": numeric argument required\n", 28);
		free_all(all);
		close(tty_fd);
		exit(2);
	}
	code = (unsigned char)ft_atoi(cmd->args[1]);
	free_all(all);
	close(tty_fd);
	exit(code);
}

void	ft_exit(t_cmd *cmd, t_all *all)
{
	int	arg_count;
	int	tty_fd;

	tty_fd = print_exit_msg();
	arg_count = count_arg(cmd->args);
	if (arg_count == 1)
	{
		free_all(all);
		close(tty_fd);
		exit(all->last_status_exit);
	}
	else if (arg_count == 2)
		exit_with_code(cmd, all, tty_fd);
	else if (arg_count > 2)
	{
		write(tty_fd, "exit: too many arguments\n", 25);
		all->last_status_exit = 1;
	}
	if (tty_fd >= 0)
		close(tty_fd);
}
