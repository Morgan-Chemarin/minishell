/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:20:39 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/12 23:28:43 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_words(char **words)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!words || !words[0])
	{
		if (words)
			free(words);
		return (ft_strdup(""));
	}
	result = ft_strdup(words[0]);
	i = 1;
	while (words[i])
	{
		tmp = result;
		result = ft_strjoin_3(tmp, "\3", words[i]);
		free(tmp);
		i++;
	}
	free_array_str(words);
	return (result);
}

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			if (env->value)
				return (env->value);
			return ("");
		}
		env = env->next;
	}
	return ("");
}
