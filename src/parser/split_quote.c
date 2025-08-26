/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:52 by dev               #+#    #+#             */
/*   Updated: 2025/08/25 02:59:51 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_word(char *result, char *word)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin(tmp, word);
	free(tmp);
	free(word);
	return (result);
}

char	*extract_plain_word(char *line, int *i, t_env *env, int skip_expand)
{
	int		start;
	char	*word;
	char	*expanded;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && \
		line[*i] != '|' && line[*i] != '<' && line[*i] != '>' && \
		line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (NULL);
	if (!skip_expand)
	{
		expanded = expand_variables(word, env, 0);
		free(word);
		if (!expanded)
			return (NULL);
		word = expanded;
	}
	return (word);
}

char	*extract_word(char *line, int *i, t_env *env, int skip_expand)
{
	char	*word;
	char	*result;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (line[*i] && !ft_isspace(line[*i]) && \
		line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '"')
			word = handle_quotes(line, i, skip_expand, env);
		else
			word = extract_plain_word(line, i, env, skip_expand);
		if (!word)
			return (free(result), NULL);
		result = append_word(result, word);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	handle_token(char *line, int *i, char **tokens, t_env *env)
{
	static int	heredoc = 0;

	if (is_double_operator(&line[*i], "<<", i))
		return (tokens[0] = ft_strdup("<<"), heredoc = 1, 1);
	else if (is_double_operator(&line[*i], ">>", i))
		return (tokens[0] = ft_strdup(">>"), 1);
	else if (is_single_operator(line[*i]))
	{
		if (line[*i] == '>' || line[*i] == '<')
		{
			if (line[*i + 1] && (line[*i + 1] == '"' || line[*i + 1] == '\''))
				return (tokens[0] = extract_word(line, i, env, 0), 1);
		}
		return (tokens[0] = ft_substr(line, (*i)++, 1), 1);
	}
	else if (heredoc)
		return (tokens[0] = extract_delimiter(line, i), heredoc = 0, 1);
	else
		return (tokens[0] = extract_word(line, i, env, 0), 1);
}

char	**split_with_quote(char *line, t_env *env)
{
	char	**tokens;
	int		i;
	int		j;
	int		nb;

	i = 0;
	j = 0;
	nb = count_tokens(line);
	tokens = malloc(sizeof(char *) * (nb + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (!handle_token(line, &i, &tokens[j], env) || !tokens[j])
			return (free_array_str(tokens), NULL);
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}
