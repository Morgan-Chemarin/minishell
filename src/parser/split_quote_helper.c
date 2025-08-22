/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:19:43 by dev               #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quoted_word(char *line, int *i, char quote)
{
	int		start;
	int		len;
	char	*word;

	len = 0;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (line[*i])
		(*i)++;
	word = ft_substr(line, start, len);
	return (word);
}

char	*extract_quoted(char *line, int *i, int skip_expand, t_env *env)
{
	char	quote;
	char	*word;
	char	*expanded;

	quote = line[*i];
	word = get_quoted_word(line, i, quote);
	if (!word)
		return (NULL);
	if (!skip_expand && quote == '"')
	{
		expanded = expand_variables(word, env);
		free(word);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
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
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>'))
			i += 2;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i++;
		else
			while (line[i] && !ft_isspace(line[i])
				&& line[i] != '|' && line[i] != '<' && line[i] != '>')
				i++;
		count++;
	}
	return (count);
}
