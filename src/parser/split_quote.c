/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/07/15 17:47:12 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_token(char *line, t_env *env, char **tokens, int ijh[3])
{
	if (is_double_operator(&line[ijh[0]], "<<", &ijh[0]))
	{
		tokens[ijh[1]++] = ft_strdup("<<");
		ijh[2] = 1;
	}
	else if (is_double_operator(&line[ijh[0]], ">>", &ijh[0]))
		tokens[ijh[1]++] = ft_strdup(">>");
	else if (is_single_operator(line[ijh[0]]))
		tokens[ijh[1]++] = ft_substr(line, ijh[0]++, 1);
	else if (ijh[2])
	{
		skip_spaces(line, &ijh[0]);
		tokens[ijh[1]++] = extract_word(line, &ijh[0], env, 1);
		ijh[2] = 0;
	}
	else
		tokens[ijh[1]++] = extract_word(line, &ijh[0], env, 0);
}

char	**split_with_quote(char *line, t_env *env)
{
	char	**tokens;
	int		ijh[3];

	ijh[0] = 0;
	ijh[1] = 0;
	ijh[2] = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[ijh[0]])
	{
		skip_spaces(line, &ijh[0]);
		if (!line[ijh[0]])
			break ;
		parse_token(line, env, tokens, ijh);
	}
	tokens[ijh[1]] = NULL;
	return (tokens);
}

char	*extract_word(char *line, int *i, t_env *env, int skip_expand)
{
	char	*word;
	char	*expanded;
	int		start;
	int		len;

	start = *i;
	len = 0;
	if (line[*i] == '\'' || line[*i] == '"')
		return (extract_quoted(line, i, skip_expand, env));
	while (line[*i] && !isspace(line[*i]) && \
			line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		(*i)++;
		len++;
	}
	word = ft_substr(line, start, len);
	if (!skip_expand)
	{
		expanded = expand_variables(word, env);
		free(word);
		word = expanded;
	}
	return (word);
}
