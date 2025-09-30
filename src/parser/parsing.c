/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 17:21:35 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_cmd **head, t_cmd **current, t_token *tokens)
{
	t_cmd	*new;
	int		capacity;

	new = new_cmd();
	if (!new)
	{
		free_cmd(*head);
		return (NULL);
	}
	capacity = compute_args_capacity(tokens);
	new->args = malloc(sizeof(char *) * (capacity + 1));
	if (!new->args)
	{
		free(new);
		free_cmd(*head);
		return (NULL);
	}
	new->redir = NULL;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}

int	process_word_token(t_cmd *cmd, t_token *token, int *i)
{
	char	**fields;

	strip_inplace(token->value, '\1');
	if (!ft_strchr(token->value, '\3'))
	{
		cmd->args[(*i)++] = ft_strdup(token->value);
		if (!cmd->args[*i - 1])
			return (0);
		return (1);
	}
	fields = ft_split(token->value, '\3');
	if (!fields)
		return (0);
	return (add_fields_to_args(cmd, fields, i));
}

int	process_redir_token(t_cmd *cmd, t_token **tokens)
{
	t_token_type	type;
	int				success;

	type = (*tokens)->type;
	success = 1;
	if (!(*tokens)->next)
		return (1);
	strip_inplace((*tokens)->next->value, '\1');
	if (type == REDIR_IN)
		success = add_redir(cmd, R_IN, (*tokens)->next->value);
	else if (type == REDIR_OUT)
		success = add_redir(cmd, R_OUT, (*tokens)->next->value);
	else if (type == REDIR_APPEND)
		success = add_redir(cmd, R_APPEND, (*tokens)->next->value);
	else if (type == REDIR_HEREDOC)
		success = add_redir(cmd, R_HEREDOC, (*tokens)->next->value);
	if (!success)
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

int	process_token(t_cmd *cmd, t_token **tokens, int *i)
{
	t_token_type	type;

	type = (*tokens)->type;
	if (type == WORD)
		return (process_word_token(cmd, *tokens, i));
	else if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == REDIR_HEREDOC)
		return (process_redir_token(cmd, tokens));
	return (1);
}

t_cmd	*parser(t_token *tokens, t_all *all)
{
	t_cmd	*head;
	t_cmd	*current;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (!create_cmd(&head, &current, tokens))
			return (NULL);
		if (!parse_single_cmd(current, &tokens))
		{
			free_array_str(current->args);
			free_cmd(head);
			return (NULL);
		}
		set_cmd_type(current);
	}
	if (!prepare_all_heredocs(head, all))
	{
		free_cmd(head);
		return (NULL);
	}
	return (head);
}
