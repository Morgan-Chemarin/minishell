/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:38:33 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:33:47 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redir(t_cmd *cmd, t_redirection_type type, char *value)
{
	t_redirection	*new;
	t_redirection	*tmp;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (0);
	new->type = type;
	new->file = ft_strdup(value);
	new->next = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
