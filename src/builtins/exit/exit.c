/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:29 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/25 01:36:36 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	int	i;

	i = 0;
	write(1, "exit\n", 5);
	if (count_arg(cmd->args) == 1)
	{
		//IL FAUT TOUS FREE
		exit(0);
	}
	else if (count_arg(cmd->args) == 2)
	{
		//IL FAUT TOUS FREE
		while (cmd->args[1][i])
		{
			if (!(cmd->args[1][i] >= '0' && cmd->args[1][i] <= '9'))
			{
				write(2, "exit: numeric argument required\n", 32);
				exit(2);
			}
			i++;
		}
		exit(ft_atoi(cmd->args[1]));
	}
	else if (count_arg(cmd->args) > 2)
		write(2, "exit: too many arguments\n", 25);
}
