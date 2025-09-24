/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:59:31 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/24 11:31:40 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stateful_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	return (!ft_strcmp(cmd->args[0], "cd")
		|| !ft_strcmp(cmd->args[0], "export")
		|| !ft_strcmp(cmd->args[0], "unset")
		|| !ft_strcmp(cmd->args[0], "exit"));
}

void	exec_builtin(t_cmd *cmd, t_env **env, t_all *all)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		all->last_status_exit = ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		all->last_status_exit = ft_cd(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		all->last_status_exit = ft_pwd();
	else if (!ft_strcmp(cmd->args[0], "export"))
		all->last_status_exit = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		all->last_status_exit = ft_unset(env, cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		all->last_status_exit = ft_env(*env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
	{
		all->env = *env;
		ft_exit(cmd, all);
	}
}
