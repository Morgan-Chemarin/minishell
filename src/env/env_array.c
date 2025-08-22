/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:38:18 by dev               #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	if (!res)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (res);
}

int	count_exportable_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**fill_envp_array(t_env *env, char **envp)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			envp[i] = ft_strjoin_3(tmp->name, "=", tmp->value);
			if (!envp[i])
			{
				free_split(envp);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_list_to_array(t_env *env)
{
	int		count;
	char	**envp;

	count = count_exportable_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	envp = fill_envp_array(env, envp);
	return (envp);
}
