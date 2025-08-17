/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:57:04 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/14 21:15:35 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env(char **arg)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(arg[0]);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (arg[1])
	{
		new->value = ft_strdup(arg[1]);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, char **arg)
{
	t_env	*new;

	new = create_env(arg);
	if (!new)
	{
		free_split(arg);
		return ;
	}
	add_env_node(env, new);
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
