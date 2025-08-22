/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:42:53 by dev               #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	handle_exec_error(char *cmd)
{
	if (is_directory(cmd))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_last_status_exit = 126;
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_last_status_exit = 126;
	}
	else
		g_last_status_exit = 0;
}

void	check_access_exec(char *cmd, char **args, char **envp)
{
	if (access(cmd, F_OK) != 0)
	{
		if (ft_strchr(cmd, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_last_status_exit = 127;
		}
		return ;
	}
	handle_exec_error(cmd);
	if (g_last_status_exit == 0)
	{
		execve(cmd, args, envp);
		perror("minishell");
		g_last_status_exit = 126;
	}
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
		if (access(path, X_OK && !is_directory(path)) == 0)
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
	if (ft_strcmp(cmd, "..") == 0)
		return (NULL);
	tmp = env;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (NULL);
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (NULL);
	path = search_in_paths(paths, cmd);
	free_split(paths);
	return (path);
}
