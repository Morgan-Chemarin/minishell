/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:39:41 by dev               #+#    #+#             */
/*   Updated: 2025/06/18 15:56:25 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	check_cd(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (1);
	if (cmd->args[2])
		return (printf("trop dargument\n"), 0);
	return (1);
}

int	check_exit(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (1);
	if (cmd->args[2])
		return (printf("trop dargument\n"), 0);
	return (1);
}

//check unset export env echo pwd

int	check_builtins_args(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
		
	if (!strcmp(cmd->args[0], "cd"))
		return (check_cd(cmd));
	if (!strcmp(cmd->args[0], "exit"))
		return (check_exit(cmd));
	//idem

	return (1);
}