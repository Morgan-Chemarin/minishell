/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:56:42 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/24 02:42:10 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_env **env, char *old_cwd)
{
	char	*cwd;
	t_env	*tmp;

	tmp = *env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		write(2, "cd: error retrieving current directory\n", 39);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			set_env_var(tmp, cwd);
		else if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			set_env_var(tmp, old_cwd);
		tmp = tmp->next;
	}
	if (cwd)
		free(cwd);
}

char	*find_var(t_env **env, char	*var)
{
	char	*path;
	t_env	*tmp;

	tmp = *env;
	path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			if (tmp->value)
				path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

int	ft_cd_exec(t_cmd *cmd, t_env **env)
{
	int		result_path;
	char	*path;
	char	*old_cwd;

	old_cwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		path = find_var(env, "HOME");
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
	update_envp(env, old_cwd);
	if (old_cwd)
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
