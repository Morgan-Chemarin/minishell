/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:17:17 by dev               #+#    #+#             */
/*   Updated: 2025/08/17 13:10:47 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_env_node(t_env *node, char *env_str)
{
	char	*equal_sign;
	size_t	name_len;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
		return (0);
	name_len = equal_sign - env_str;
	node->name = ft_strndup(env_str, name_len);
	if (!node->name)
		return (0);
	node->value = ft_strdup(equal_sign + 1);
	if (!node->value)
	{
		free(node->name);
		return (0);
	}
	return (1);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!fill_env_node(node, env_str))
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

t_env	*envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	while (*envp)
	{
		new_node = create_env_node(*envp);
		if (!new_node)
		{
			free_env(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		envp++;
	}
	return (head);
}
