/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:39:36 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/24 22:16:48 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	env_to_array(t_env *env, t_env **array, int size)
{
	int	i;

	i = 0;
	while (i < size && env)
	{
		array[i] = env;
		env = env->next;
		i++;
	}
}

void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(array[i]->name, array[j]->name) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_env_export(t_env *env)
{
	int		size;
	int		i;
	t_env	**array;

	i = 0;
	size = env_size(env);
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	env_to_array(env, array, size);
	sort_env_array(array, size);
	while (i < size)
	{
		ft_putstr("declare -x ");
		ft_putstr(array[i]->name);
		if (array[i]->value)
		{
			write(1, "=\"", 2);
			ft_putstr(array[i]->value);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	free(array);
}
