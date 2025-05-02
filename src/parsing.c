/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/05/02 16:19:57 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;

	while (tokens)
	{
		t_cmd *new = new_cmd();
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		int	arg_count = count_args(tokens);
		current->args = malloc(sizeof(char *) * (arg_count + 1));
		int	i = 0;

		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
				current->args[i++] = strdup(tokens->value);
			else if (tokens->type == REDIR_IN)
			{
				tokens = tokens->next;
				if (tokens)
					current->input_file = strdup(tokens->value);
			}
			else if (tokens->type == REDIR_OUT)
			{
				tokens = tokens->next;
				if (tokens)
				{
					current->output_file = strdup(tokens->value);
					current->append = 0;
				}
			}
			else if (tokens->type == REDIR_APPEND)
			{
				tokens = tokens->next;
				if (tokens)
				{
					current->output_file = strdup(tokens->value);
					current->append = 1;
				}
			}
			tokens = tokens->next;
		}
		current->args[i] = NULL;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}

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
	return (head);
}
