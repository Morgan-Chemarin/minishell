/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:06:47 by dev               #+#    #+#             */
/*   Updated: 2025/08/17 13:10:33 by dev              ###   ########.fr       */
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

char	*handle_exit_status(char *result, int *i)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(g_last_status_exit);
	if (!status)
	{
		free(result);
		return (NULL);
	}
	tmp = result;
	result = ft_strjoin(tmp, status);
	free(tmp);
	free(status);
	if (!result)
		return (NULL);
	*i += 2;
	return (result);
}

char	*handle_env_variable(char *result, char *str, int *i, t_env *env)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	value = get_env_value(var_name, env);
	tmp = result;
	result = ft_strjoin(tmp, value);
	free(tmp);
	free(var_name);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_regular_char(char *result, char c, int *i)
{
	char	tmp_char[2];
	char	*tmp;

	tmp_char[0] = c;
	tmp_char[1] = '\0';
	tmp = result;
	result = ft_strjoin(tmp, tmp_char);
	free(tmp);
	(*i)++;
	return (result);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		i;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			result = handle_exit_status(result, &i);
		else if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = handle_env_variable(result, str, &i, env);
		else
			result = handle_regular_char(result, str[i], &i);
		if (!result)
			return (NULL);
	}
	return (result);
}
