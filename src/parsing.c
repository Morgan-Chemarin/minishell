/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/04/22 14:11:27 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*tmp;
	int		arg_count;

	cmd = malloc(sizeof(t_cmd));
	tmp = tokens;
	arg_count = 0;
	cmd->args = malloc(sizeof(char *) * 100); // trouver moyen davoir le nombre de mot avant
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	while (tmp)
	{
		if (tmp->type == WORD)
			cmd->args[arg_count++] = ft_strdup(tmp->value);
		else if (tmp->type == REDIR_IN && tmp->next)
			cmd->input_file = ft_strdup(tmp->next->value);
		else if (tmp->type == REDIR_OUT && tmp->next)
			cmd->output_file = ft_strdup(tmp->next->value);
		else if (tmp->type == REDIR_APPEND && tmp->next)
		{
			cmd->output_file = ft_strdup(tmp->next->value);
			cmd->append = 1;
		}
		tmp = tmp->next;
	}
	cmd->args[arg_count] = NULL;
	return (cmd);
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
