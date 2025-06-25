/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/06/25 15:04:04 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	free_tokens(char **tokens, int count)
// {
// 	while (count > 0)
// 	{
// 		count--;
// 		free(tokens[count]);
// 	}
// 	free(tokens);
// }

char	*extract_word(char *line, int *i, t_env *env)
{
	char	*word;
	char	*expanded;
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
		(*i)++;
		word = ft_substr(line, start, len);
		if (quote == '"')
		{
			expanded = expand_variables(word, env);
			free(word);
			word = expanded;
		}
	}
	else
	{
		while (line[*i] && !isspace(line[*i]) && \
				line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		{
			(*i)++;
			len++;
		}
		word = ft_substr(line, start, len);
		expanded = expand_variables(word, env);
		free(word);
		word = expanded;
	}
	return (word);
}

char	**split_with_quote(char *line, t_env *env)
{
	char	**tokens;
	char	*word;
	int		i;
	int		j;

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
		if (line[i] == '<' && line[i + 1] == '<')
		{
			tokens[j++] = ft_strdup("<<");
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			tokens[j++] = ft_strdup(">>");
			i += 2;
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			tokens[j++] = ft_substr(line, i, 1);
			i++;
		}
		else
		{
			word = extract_word(line, &i, env);
			tokens[j++] = word;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

int	count_unclosed_quotes(const char *line)
{
	int		i;
	char	quote;
	int		open;

	i = 0;
	open = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && (!quote || quote == line[i]))
		{
			if (!quote)
				quote = line[i];
			else
				quote = 0;
		}
		i++;
	}
	if (quote)
		return (1);
	return (0);
}
