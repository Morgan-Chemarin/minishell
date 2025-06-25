/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:06:47 by dev               #+#    #+#             */
/*   Updated: 2025/06/25 14:44:04 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*tmp;
	char	*var_name;
	char	*value;
	char	tmp_char[2];
	int		i;
	int		start;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && \
			(ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substr(str, start, i - start);
			if (!var_name)
				return (free(result), NULL);
			value = get_env_value(var_name, env);
			tmp = result;
			result = ft_strjoin(tmp, value);
			free(tmp);
			free(var_name);
			if (!result)
				return (NULL);
		}
		else
		{
			tmp_char[0] = str[i];
			tmp_char[1] = '\0';
			i++;
			tmp = result;
			result = ft_strjoin(tmp, tmp_char);
			free(tmp);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}
