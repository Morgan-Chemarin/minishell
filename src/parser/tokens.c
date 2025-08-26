/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:24:04 by dev               #+#    #+#             */
/*   Updated: 2025/08/24 01:37:56 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	else if (!ft_strcmp(s, "<"))
		return (REDIR_IN);
	else if (!ft_strcmp(s, ">"))
		return (REDIR_OUT);
	else if (!ft_strcmp(s, ">>"))
		return (REDIR_APPEND);
	else if (!ft_strcmp(s, "<<"))
		return (REDIR_HEREDOC);
	else
		return (WORD);
}

t_token	*new_token(char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = get_token_type(value);
	new->next = NULL;
	return (new);
}

t_token	*create_struct_tokens(char **pre_token)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (pre_token[i])
	{
		new = new_token(pre_token[i]);
		if (!new)
		{
			free_token(head);
			free_array_str(pre_token);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		i++;
	}
	return (head);
}
