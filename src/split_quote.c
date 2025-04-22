/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/04/22 14:11:14 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;

	start = *i;
	len = 0;
	quote = 0;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		start = *i;
		while (line[*i] && line[*i] != quote)
		{
			(*i)++;
			len++;
		}
		if (line[*i] == quote)
			(*i)++;
		// else si ya pas de qote pour fermer
	}
	else
	{
		while (line[*i] && !isspace(line[*i]) && \
			line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		{
			(*i)++;
			len++;
		}
	}
	return (strndup(line + start, len));
}

char	**split_with_quote(char *line)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * 256); // trouver moyen davoir le nombre de mot avant
	i = 0;
	j = 0;
	while (line[i])
	{
		while (isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				tokens[j] = strndup("<<", 2);
				j++;
				i += 2;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				tokens[j] = strndup(">>", 2);
				j++;
				i += 2;
			}
			else
			{
				tokens[j] = strndup(&line[i], 1);
				j++;
				i++;
			}
		}
		else
		{
			tokens[j] = extract_word(line, &i);
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
