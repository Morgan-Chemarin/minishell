/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:42:53 by dev               #+#    #+#             */
/*   Updated: 2025/08/12 17:32:39 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(const char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	check_access_exec(char *cmd, char **args, char **envp)
{
	if (is_directory(cmd))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_last_status_exit = 126;
		return ;
	}
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        if (ft_strchr(cmd, '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
        ft_free_split(envp);
        g_last_status_exit = 127;
		return ;
	}
	else if (access(cmd, X_OK) != 0)
	{
		perror(cmd);
		ft_free_split(envp);
		g_last_status_exit = 126;
		return ;
	}
	execve(cmd, args, envp);
	perror("minishell");
	ft_free_split(envp);
	g_last_status_exit = 126;
}

static char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (paths && paths[i])
	{
		path = ft_strjoin_3(paths[i], "/", cmd);
		if (!path)
			break ;
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	t_env	*tmp;
	char	**paths;
	char	*path;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	tmp = env;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (NULL);
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (NULL);
	path = search_in_paths(paths, cmd);
	ft_free_split(paths);
	return (path);
}
