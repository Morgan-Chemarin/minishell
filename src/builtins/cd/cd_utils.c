/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:41:23 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/24 02:42:15 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_var(t_env *node, char *new_value)
{
	free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
}

int	no_home(char *old_cwd, char *path)
{
	perror("cd");
	if (old_cwd)
		free(old_cwd);
	if (path)
		free(path);
	return (1);
}
