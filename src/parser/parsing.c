/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/07/24 09:04:43 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new;
	int		i;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		new = new_cmd();
		if (!new)
		{
			free_cmd(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		current->args = malloc(sizeof(char *) * (count_args(tokens) + 1));
		if (!current->args)
		{
			free_cmd(head);
			return (NULL);
		}
		i = 0;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
			{
				current->args[i] = ft_strdup(tokens->value);
				if (!current->args[i])
				{
					free_array_str(current->args);
					current->args = NULL;
					free_cmd(head);
					return (NULL);
				}
				i++;
			}
			else if (tokens->type == REDIR_IN)
			{
				tokens = tokens->next;
				if (tokens)
				{
					if (current->input_file)
						free(current->input_file);
					current->input_file = ft_strdup(tokens->value);
					if (!current->input_file)
					{
						free_cmd(head);
						return (NULL);
					}
				}
			}
			else if (tokens->type == REDIR_HEREDOC)
			{
				tokens = tokens->next;
				if (tokens)
				{
					current->heredoc_delim = ft_strdup(tokens->value);
					if (!current->heredoc_delim)
					{
						free_cmd(head);
						return (NULL);
					}
					current->has_heredoc = 1;
				}
			}
			else if (tokens->type == REDIR_OUT)
			{
				tokens = tokens->next;
				if (tokens)
				{
					if (current->output_file)
						free(current->output_file);
					current->output_file = ft_strdup(tokens->value);
					if (!current->output_file)
					{
						free_cmd(head);
						return (NULL);
					}
					current->append = 0;
				}
			}
			else if (tokens->type == REDIR_APPEND)
			{
				tokens = tokens->next;
				if (tokens)
				{
					if (current->output_file)
						free(current->output_file);
					current->output_file = ft_strdup(tokens->value);\
					if (!current->output_file)
					{
						free_cmd(head);
						return (NULL);
					}
					current->append = 1;
				}
			}
			tokens = tokens->next;
		}
		current->args[i] = NULL;
		if (current->args[0]
			&& (!ft_strcmp(current->args[0], "cd")
			|| !ft_strcmp(current->args[0], "echo")
			|| !ft_strcmp(current->args[0], "env")
			|| !ft_strcmp(current->args[0], "exit")
			|| !ft_strcmp(current->args[0], "export")
			|| !ft_strcmp(current->args[0], "unset")
			|| !ft_strcmp(current->args[0], "pwd")))
			current->type = CMD_BUILTNS;
		else
			current->type = CMD_EXTERNAL;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}

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

t_token	*create_struct_tokens(char **pre_token)
{
	t_token	*head;
	t_token	*new;
	t_token	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (pre_token[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
		{
			free_token(head);
			free_array_str(pre_token);
			return (NULL);
		}
		new->value = ft_strdup(pre_token[i]);
		if (!new->value)
		{
			free(new);
			free_token(head);
			free_array_str(pre_token);
			return (NULL);
		}
		new->type = get_token_type(pre_token[i]);
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
	free_array_str(pre_token);
	return (head);
}
