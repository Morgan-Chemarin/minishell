/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:18:36 by dev               #+#    #+#             */
/*   Updated: 2025/08/17 11:50:04 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

int	is_single_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_double_operator(char *s, const char *op, int *i)
{
	if (s[0] == op[0] && s[1] == op[1])
	{
		*i += 2;
		return (1);
	}
	return (0);
}

char	*extract_delimiter(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}
