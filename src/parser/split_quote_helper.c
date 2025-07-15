/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:19:43 by dev               #+#    #+#             */
/*   Updated: 2025/07/15 18:25:01 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_if_needed(char *line, char quote, t_env *env)
{
	char	*expanded;
	char	*res;

	res = ft_substr(line, 0, ft_strlen(line));
	if (quote == '"')
	{
		expanded = expand_variables(res, env);
		free(res);
		return (expanded);
	}
	return (res);
}

char	*extract_quoted(char *line, int *i, int skip_expand, t_env *env)
{
	char	quote;
	int		start;
	int		len;
	char	*word;

	quote = line[*i];
	(*i)++;
	start = *i;
	len = 0;
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
		len++;
	}
	(*i)++;
	if (skip_expand)
		word = ft_substr(line, start - 1, len + 2);
	else
		word = expand_if_needed(&line[start], quote, env);
	return (word);
}

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>'))
			i += 2;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i++;
		else
			while (line[i] && !isspace(line[i])
				&& line[i] != '|' && line[i] != '<' && line[i] != '>')
				i++;
		count++;
	}
	return (count);
}
