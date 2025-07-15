/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:12:35 by dev               #+#    #+#             */
/*   Updated: 2025/07/15 19:33:29 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_token_type(char *s)
{
	if (!strcmp(s, "|"))
		return (PIPE);
	else if (!strcmp(s, "<"))
		return (REDIR_IN);
	else if (!strcmp(s, ">"))
		return (REDIR_OUT);
	else if (!strcmp(s, ">>"))
		return (REDIR_APPEND);
	else if (!strcmp(s, "<<"))
		return (REDIR_HEREDOC);
	else
		return (WORD);
}

t_token	*create_struct_tokens(char **split)
{
	t_token	*head;
	t_token	*new;
	t_token	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (split[i])
	{
		new = malloc(sizeof(t_token));
		new->value = ft_strdup(split[i]);
		new->type = get_token_type(split[i]);
		new->next = NULL;
		if (!head)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	free_array_str(split);
	return (head);
}
