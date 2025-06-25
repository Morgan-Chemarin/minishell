/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:11:29 by dev               #+#    #+#             */
/*   Updated: 2025/06/24 17:14:18 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_env **env, t_cmd *cmd)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 0;
	while (cmd->args[++i])
	{
		previous = NULL;
		current = *env;
		while (current)
		{
			if (ft_strcmp(current->name, cmd->args[i]) == 0)
			{
				if (previous)
					previous->next = current->next;
				else
					*env = current->next;
				free(current->name);
				free(current->value);
				free(current);
			}
			previous = current;
			current = current->next;
		}
	}
}
