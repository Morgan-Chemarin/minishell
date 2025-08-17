/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:59:31 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/16 22:00:06 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stateful_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	return (!strcmp(cmd->args[0], "cd")
		|| !strcmp(cmd->args[0], "export")
		|| !strcmp(cmd->args[0], "unset")
		|| !strcmp(cmd->args[0], "exit"));
}

void	exec_builtin(t_cmd *cmd, t_env **env, t_all *all)
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
	{
		all->env = *env;
		ft_exit(cmd, all);
	}
}
