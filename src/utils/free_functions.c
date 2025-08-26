/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:31:29 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:31:17 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_redirs(t_redirection *r)
{
	t_redirection	*tmp;

	while (r)
	{
		tmp = r->next;
		if (r->file)
			free(r->file);
		free(r);
		r = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_array_str(cmd->args);
		if (cmd->redir)
			free_redirs(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_export_add_env(t_env *new, char **arg)
{
	if (arg)
		free_array_str(arg);
	if (new)
	{
		if (new->name)
			free(new->name);
		free(new);
	}
}
