/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:29 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/18 17:48:44 by dev              ###   ########.fr       */
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


// int main(void)
// {
//     t_cmd cmd1 = {.args = (char *[]){"exit", NULL}};
//     t_cmd cmd2 = {.args = (char *[]){"exit", "42", NULL}};

//     printf("Test 1 (exit sans argument):\n");
//     //ft_exit(&cmd1);

//     printf("Test 2 (exit avec code 42):\n");
//     ft_exit(&cmd2);;

//     return 0;
// }