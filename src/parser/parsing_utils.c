/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:12:30 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/24 15:08:41 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_fields_in_word(char *s)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	if (!*s)
		return (1);
	if (!ft_strchr(s, '\3'))
		return (1);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == '\3')
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != '\3')
			i++;
	}
	return (count);
}

int	compute_args_capacity(t_token *tokens)
{
	int		count;
	t_token	*t;

	count = 0;
	t = tokens;
	while (t && t->type != PIPE)
	{
		if (t->type == WORD)
			count += count_fields_in_word(t->value);
		else if ((t->type == REDIR_IN || t->type == REDIR_OUT
				|| t->type == REDIR_APPEND || t->type == REDIR_HEREDOC)
			&& t->next)
			t = t->next;
		t = t->next;
	}
	return (count);
}

void	strip_inplace(char *s, char ch)
{
	int	r;
	int	w;

	if (!s)
		return ;
	r = 0;
	w = 0;
	while (s[r])
	{
		if (s[r] != ch)
			s[w++] = s[r];
		r++;
	}
	s[w] = '\0';
}

int	add_fields_to_args(t_cmd *cmd, char **fields, int *i)
{
	int	k;

	k = 0;
	while (fields[k])
	{
		if (fields[k][0] != '\0')
		{
			cmd->args[(*i)++] = ft_strdup(fields[k]);
			if (!cmd->args[*i - 1])
			{
				free_array_str(fields);
				return (0);
			}
		}
		k++;
	}
	free_array_str(fields);
	return (1);
}
