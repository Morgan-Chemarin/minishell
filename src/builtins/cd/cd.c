/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:56:42 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:51:35 by dev              ###   ########.fr       */
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
	path = NULL;
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

int	no_home(char *old_cwd, char *path)
{
	perror("cd");
	free(old_cwd);
	free(path);
	return (1);
}

int	ft_cd_exec(t_cmd *cmd, t_env **env)
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
			write(2, "cd: HOME not set\n", 17);
			free(old_cwd);
			return (1);
		}
	}
	else
		path = ft_strdup(cmd->args[1]);
	result_path = chdir(path);
	if (result_path == -1)
		return (no_home(old_cwd, path));
	else
		update_envp(env, old_cwd);
	free(old_cwd);
	free(path);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env **env)
{
	int	status;

	status = 0;
	if (count_arg(cmd->args) > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	status = ft_cd_exec(cmd, env);
	return (status);
}
