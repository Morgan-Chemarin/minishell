/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:34:18 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:53:24 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int    ft_unset(t_env **env, t_cmd *cmd)
{
    int        i;
    t_env    *current;
    t_env    *previous;
    t_env    *to_free;

    i = -1;
    while (cmd->args[++i])
    {
        previous = NULL;
        current = *env;
        while (current)
        {
            if (ft_strcmp(current->name, cmd->args[i]) == 0)
            {
                to_free = current;
                if (previous)
                    previous->next = current->next;
                else
                    *env = current->next;
                current = current->next;
                free(to_free->name);
                if (to_free->value)
                    free(to_free->value);
                free(to_free);
                continue;
            }
            previous = current;
            current = current->next;
        }
    }
    return (0);
}
