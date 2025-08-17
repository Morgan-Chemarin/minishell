/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:38:33 by dev               #+#    #+#             */
/*   Updated: 2025/08/17 12:49:22 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_input(t_cmd *cmd, t_token **tokens)
{
	char	*tmp;

	*tokens = (*tokens)->next;
	if (!*tokens)
		return (0);
	tmp = ft_strdup((*tokens)->value);
	if (!tmp)
		return (0);
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = tmp;
	return (1);
}

int	set_output(t_cmd *cmd, t_token **tokens, int append)
{
	char	*tmp;

	*tokens = (*tokens)->next;
	if (!*tokens)
		return (0);
	tmp = ft_strdup((*tokens)->value);
	if (!tmp)
		return (0);
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = tmp;
	cmd->append = append;
	return (1);
}

int	set_heredoc(t_cmd *cmd, t_token **tokens)
{
	char	*tmp;

	*tokens = (*tokens)->next;
	if (!*tokens)
		return (0);
	tmp = ft_strdup((*tokens)->value);
	if (!tmp)
		return (0);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = tmp;
	cmd->has_heredoc = 1;
	return (1);
}
