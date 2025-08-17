/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:34:18 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/15 18:27:24 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_env_var(t_env **env, char *var_name)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free_env_node(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_env **env, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(env, cmd->args[i]);
		i++;
	}
	return (0);
}
