/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:56:42 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/25 01:38:48 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_envp(t_env **env, char *old_cwd)
{
	char	*cwd;
	t_env	*tmp;

	tmp = *env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		free(old_cwd);
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(cwd);
		}
		else if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_cwd);
		}
		tmp = tmp->next;
	}
	free(cwd);
}

char	*find_home(t_env **env)
{
	char	*path;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "HOME") == 0)
		{
			path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

void	ft_cd_exec(t_cmd *cmd, t_env **env)
{
	int		result_path;
	char	*path;
	char	*old_cwd;

	old_cwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		path = find_home(env);
		if (!path)
		{
			perror("cd");
			free(old_cwd);
			return ;
		}
	}
	else
		path = ft_strdup(cmd->args[1]);
	result_path = chdir(path);
	if (result_path == -1)
		perror("cd");
	else
		update_envp(env, old_cwd);
	free(old_cwd);
	free(path);
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	if (count_arg(cmd->args) > 2)
		return ;
	ft_cd_exec(cmd, env);
}
