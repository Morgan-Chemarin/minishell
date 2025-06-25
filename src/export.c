/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:57:04 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/24 17:56:42 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// void	add_env(t_env **env, char *arg)
// {
// 	t_env	*new;
// 	t_env	*tmp;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->name = ft_strdup(arg);
// 	new->value = NULL;
// 	new->next = NULL;
// 	if (*env == NULL)
// 	{
// 		*env = new;
// 		return ;
// 	}
// 	tmp = *env;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// void	update_env(t_env **env, char *arg)
// {
// 	t_env	*tmp;

// 	tmp = *env;
// 	while (tmp->next != NULL)
// 	{
// 		if (ft_strcmp(tmp->name, arg) == 0)
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_strdup(arg);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	ft_export(t_cmd *cmd, t_env **env)
// {
// 	int		i;
// 	t_env	*tmp;

// 	i = 0;
// 	if (cmd->args[1] == NULL)
// 		ft_env(env);
// 	else
// 	{
// 		while (cmd->args[++i])
// 		{
// 			tmp = *env;
// 			while (tmp->next != NULL)
// 			{
// 				if (ft_strcmp(tmp->name, cmd->args[i]) == 0)
// 					break ;
// 				tmp = tmp->next;
// 			}
// 			if (tmp->next == NULL)
// 				add_env(env, cmd->args[i]);
// 			else
// 				update_env(env, cmd->args[i]);
// 		}
// 	}
// }
