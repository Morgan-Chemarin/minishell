/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:56:42 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/24 17:00:13 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ft_strcmp(tmp->name, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(cwd);
		}
		else if (ft_strcmp(tmp->name, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_cwd);
		}
		tmp = tmp->next;
	}
	free(cwd);
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	int		result_path;
	char	*old_cwd;

	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
	{
		perror("cd");
		free(old_cwd);
	}
	result_path = chdir(cmd->args[1]);
	if (result_path == -1)
		perror("cd");
	else
	{
		update_envp(env, old_cwd);
		free(old_cwd);
	}
}
