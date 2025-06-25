/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:29 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/24 17:05:30 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	ft_exit(t_cmd *cmd)
{
	write(1, "exit\n", 5);
	if (count_arg(cmd->args) == 1)
	{
		//IL FAUT TOUS FREE
		exit(0);
	}
	if (count_arg(cmd->args) == 2)
	{
		//IL FAUT TOUS FREE
		exit(ft_atoi(cmd->args[1]));
	}
}
