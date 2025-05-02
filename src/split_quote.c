/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/05/02 16:46:29 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_tokens(char **tokens, int count)
{
	while (count > 0)
		free(tokens[--count]);
	free(tokens);
}

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
		else
			return (NULL);
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
	char	*word;

	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
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
				tokens[j++] = strndup("<<", 2), i += 2;
			else if (line[i] == '>' && line[i + 1] == '>')
				tokens[j++] = strndup(">>", 2), i += 2;
			else
				tokens[j++] = strndup(&line[i++], 1);
		}
		else
		{
			word = extract_word(line, &i);
			if (!word)
			{
				printf("Error: quote not close\n");
				free_tokens(tokens, j);
				return (NULL);
			}
			tokens[j++] = word;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
