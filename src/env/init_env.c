/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:17:17 by dev               #+#    #+#             */
/*   Updated: 2025/07/24 08:55:02 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal_sign;
		
	node = malloc(sizeof(t_env));
	if (!node)
	    return (NULL);
	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
	{
	    free(node);
	    return (NULL);
	}
	size_t name_len = equal_sign - env_str;
	node->name = ft_strndup(env_str, name_len);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(equal_sign + 1);
	if (!node->value)
	{
		free(node->name);
		free(node);
		return (NULL);
    }
	node->next = NULL;
	return (node);
}

t_env *envp_to_list(char **envp)
{
    t_env *head;
    t_env *tail;

    head = NULL;
    tail = NULL;
    while (*envp)
    {
        t_env *new_node = create_env_node(*envp);
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
