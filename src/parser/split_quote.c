/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/07/17 02:21:42 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_with_quote(char *line, t_env *env)
{
	char	**tokens;
	int		i = 0;
	int		j = 0;
	int		nb = count_tokens(line);
	int		heredoc = 0;

	tokens = malloc(sizeof(char *) * (nb + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_double_operator(&line[i], "<<", &i))
		{
			tokens[j++] = ft_strdup("<<");
			heredoc = 1;
		}
		else if (is_double_operator(&line[i], ">>", &i))
			tokens[j++] = ft_strdup(">>");
		else if (is_single_operator(line[i]))
			tokens[j++] = ft_substr(line, i++, 1);
		else if (heredoc)
		{
			tokens[j++] = extract_delimiter(line, &i);
			heredoc = 0;
		}
		else
			tokens[j++] = extract_word(line, &i, env, 0);
		
	}
	tokens[j] = NULL;
	return (tokens);
}

char	*extract_word(char *line, int *i, t_env *env, int skip_expand)
{
	char	*word;
	char	*expanded;
	char	*result;
	int		start;

	result = ft_calloc(1, 1);
	while (line[*i] && !ft_isspace(line[*i]) && \
			line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			word = extract_quoted(line, i, skip_expand, env);
		}
		else
		{
			start = *i;
			while (line[*i] && !ft_isspace(line[*i]) && \
				line[*i] != '|' && line[*i] != '<' && line[*i] != '>' && \
				line[*i] != '\'' && line[*i] != '"')
				(*i)++;
			word = ft_substr(line, start, *i - start);
			if (!skip_expand)
			{
				expanded = expand_variables(word, env);
				free(word);
				word = expanded;
			}
		}
		expanded = result;
		result = ft_strjoin(expanded, word);
		free(expanded);
		free(word);
	}
	return (result);
}
