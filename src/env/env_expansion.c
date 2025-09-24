/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:06:47 by dev               #+#    #+#             */
/*   Updated: 2025/09/24 12:11:33 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_status(char *result, int *i, t_all *all)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(all->last_status_exit);
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
	if (value == NULL)
		value = "";
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

char	*get_expansion(char *str, t_env *env, t_all *all)
{
	char	*expanded;
	int		i;

	expanded = ft_calloc(1, 1);
	if (!expanded)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			expanded = handle_exit_status(expanded, &i, all);
		else if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			expanded = handle_env_variable(expanded, str, &i, env);
		else
			expanded = handle_regular_char(expanded, str[i], &i);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}

char	*expand_variables(char *str, t_env *env, int is_quoted, t_all *all)
{
	char	*result;
	char	*expanded;
	char	**words;

	expanded = get_expansion(str, env, all);
	if (!expanded)
		return (NULL);
	if (is_quoted)
		return (expanded);
	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (NULL);
	result = join_words(words);
	return (result);
}
