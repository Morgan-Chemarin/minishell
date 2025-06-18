/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:56:42 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/18 17:58:59 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_cd(t_cmd *cmd)
{
	int		result_path;
	char	*cwd;

	result_path = chdir(cmd->args[1]);
	if (result_path == -1)
	{
		perror("cd");
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("cd");
			free(cwd);
		}
		return (cwd);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("cd");
			free(cwd);
		}
		return (cwd);
	}
}
