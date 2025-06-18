/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:03:48 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/18 17:48:44 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		i++;
		option = 1;
	}
	if (!cmd->args[i] && option != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	while (cmd->args[i])
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (option != 1)
		write(1, "\n", 1);
}

// int	main(int ac, char **av)
// {
// 	t_cmd *cmd;

// 	cmd->args = av;
// 	echo(cmd);
// }