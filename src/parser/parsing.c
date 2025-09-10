/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/09/10 18:04:14 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_cmd **head, t_cmd **current, t_token *tokens)
{
	t_cmd	*new;

	new = new_cmd();
	if (!new)
	{
		free_cmd(*head);
		return (NULL);
	}
	new->args = malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!new->args)
	{
		free(new);
		free_cmd(*head);
		return (NULL);
	}
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}

int	process_token(t_cmd *cmd, t_token **tokens, int *i)
{
	char	*val;

	if ((*tokens)->type == WORD)
	{
		val = (*tokens)->value;
		if (val[0] == '\1')
			cmd->args[*i] = ft_strdup(val + 1);
		else
			cmd->args[*i] = ft_strdup(val);
		if (!cmd->args[*i])
			return (0);
		(*i)++;
	}
	else if ((*tokens)->type == REDIR_IN && (*tokens)->next)
	{
		if (!add_redir(cmd, R_IN, (*tokens)->next->value))
			return (0);
		*tokens = (*tokens)->next;
		return (1);
	}
	else if ((*tokens)->type == REDIR_OUT && (*tokens)->next)
	{
		if (!add_redir(cmd, R_OUT, (*tokens)->next->value))
			return (0);
		*tokens = (*tokens)->next;
		return (1);
	}
	else if ((*tokens)->type == REDIR_APPEND && (*tokens)->next)
	{
		if (!add_redir(cmd, R_APPEND, (*tokens)->next->value))
			return (0);
		*tokens = (*tokens)->next;
		return (1);
	}
	else if ((*tokens)->type == REDIR_HEREDOC && (*tokens)->next)
	{
		if (!add_redir(cmd, R_HEREDOC, (*tokens)->next->value))
			return (0);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (1);
}

void	set_cmd_type(t_cmd *cmd)
{
	if (cmd->args[0]
		&& (!ft_strcmp(cmd->args[0], "cd")
			|| !ft_strcmp(cmd->args[0], "echo")
			|| !ft_strcmp(cmd->args[0], "env")
			|| !ft_strcmp(cmd->args[0], "exit")
			|| !ft_strcmp(cmd->args[0], "export")
			|| !ft_strcmp(cmd->args[0], "unset")
			|| !ft_strcmp(cmd->args[0], "pwd")))
		cmd->type = CMD_BUILTNS;
	else
		cmd->type = CMD_EXTERNAL;
}

int	parse_single_cmd(t_cmd *cmd, t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if (!process_token(cmd, tokens, &i))
			return (0);
		*tokens = (*tokens)->next;
	}
	cmd->args[i] = NULL;
	// int k = 0;
	// while (cmd->args[0][k])
	// {
	// 	printf("%d\n", cmd->args[0][k]);
	// 	k++;
	// } // pas touche cest pour le \1
	set_cmd_type(cmd);
	if (*tokens && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
	return (1);
}

t_cmd	*parser(t_token *tokens, t_env *env)
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
	}
	if (!prepare_all_heredocs(head, env))
	{
		free_cmd(head);
		return (NULL);
	}
	return (head);
}
