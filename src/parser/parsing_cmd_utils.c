/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:16:55 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/24 13:21:48 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (*tokens && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
	return (1);
}
