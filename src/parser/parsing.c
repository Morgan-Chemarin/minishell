/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:13:36 by dev               #+#    #+#             */
/*   Updated: 2025/07/15 19:33:13 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "cd")
		|| !strcmp(cmd, "echo")
		|| !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit")
		|| !strcmp(cmd, "export")
		|| !strcmp(cmd, "unset")
		|| !strcmp(cmd, "pwd"));
}

void	fill_redirections(t_cmd *cmd, t_token **tokens)
{
	t_token	*next;

	if (!*tokens || !(*tokens)->next)
		return ;
	next = (*tokens)->next;
	if ((*tokens)->type == REDIR_IN)
		cmd->input_file = ft_strdup(next->value);
	else if ((*tokens)->type == REDIR_OUT)
	{
		cmd->output_file = ft_strdup(next->value);
		cmd->append = 0;
	}
	else if ((*tokens)->type == REDIR_APPEND)
	{
		cmd->output_file = ft_strdup(next->value);
		cmd->append = 1;
	}
	else if ((*tokens)->type == REDIR_HEREDOC)
	{
		cmd->heredoc_delim = ft_strdup(next->value);
		cmd->has_heredoc = 1;
	}
	*tokens = next;
}

t_cmd	*build_cmd(t_token **tokens)
{
	t_cmd	*cmd;
	int		i;

	cmd = new_cmd();
	cmd->args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			cmd->args[i] = ft_strdup((*tokens)->value);
			i++;
		}
		else
			fill_redirections(cmd, tokens);
		*tokens = (*tokens)->next;
	}
	cmd->args[i] = NULL;
	if (is_builtin(cmd->args[0]))
		cmd->type = CMD_BUILTNS;
	else
		cmd->type = CMD_EXTERNAL;
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*cmd;

	head = NULL;
	last = NULL;
	while (tokens)
	{
		cmd = build_cmd(&tokens);
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}
