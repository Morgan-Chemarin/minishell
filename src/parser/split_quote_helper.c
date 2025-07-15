/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:19:43 by dev               #+#    #+#             */
/*   Updated: 2025/07/15 14:19:47 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_quoted(char *line, int *i, int skip_expand, t_env *env)
{
	char	quote = line[*i];
	int		start;
	int		len = 0;
	char	*word;
	char	*expanded;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++, len++;
	(*i)++;
	word = ft_substr(line, start, len);
	if (!skip_expand && quote == '"')
	{
		expanded = expand_variables(word, env);
		free(word);
		word = expanded;
	}
	return (word);
}

int	count_tokens(char *line)
{
	int	i = 0;
	int	count = 0;

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
