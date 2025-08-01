/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:57:04 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:52:58 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_split(char **split_arg)
{
	int	i;

	i = 0;
	while (split_arg[i])
	{
		free(split_arg[i]);
		i++;
	}
	free(split_arg);
}

void	add_env(t_env **env, char **arg)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_export_add_env(new, arg);
		return ;
	}
	new->name = ft_strdup(arg[0]);
	if (!new->name)
	{
		free_export_add_env(new, arg);
		return ;
	}
	if (arg[1])
	{
		new->value = ft_strdup(arg[1]);
		if (!new->value)
		{
			free_export_add_env(new, arg);
			return ;
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	if (*env == NULL)
	{
		*env = new;
		free_split(arg);
		return ;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	free_split(arg);
}

void	update_env(t_env **env, char **arg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg[0]) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(arg[1]);
			break ;
		}
		tmp = tmp->next;
	}
	free_split(arg);
}

void	ft_export_exec(char *arg, t_env **env)
{
	char	**split_arg;
	t_env	*tmp;

	split_arg = ft_split(arg, '=');
	if (!split_arg)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, split_arg[0]) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		add_env(env, split_arg);
	else if (split_arg[1])
		update_env(env, split_arg);
	else
		free_split(split_arg);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->args[1] == NULL)
		ft_env_export(*env);
	else
	{
		while (cmd->args[i])
		{
			if (!((cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z')
				|| (cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z')))
			{
				write(2, "export : not a valid identifier\n", 32);
				return (1);
			}
			else
				ft_export_exec(cmd->args[i], env);
			i++;
		}
	}
	return (0);
}
