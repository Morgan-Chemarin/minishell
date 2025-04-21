/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/04/21 18:17:45 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*rl;
	t_cmd	cmd;
	int		i;

	i = 0;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break;
		if (*rl)
			add_history(rl);
		cmd.args = ft_split(rl, ' ');
		
		while (cmd.args[i])
		{
			printf("arg[%d] = %s\n", i, cmd.args[i]);
			i++;
		}
		i = 0;
		free(rl);
	}
	return (0);
}