/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:05:22 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/18 17:50:20 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *envp)
{
	int	i;

	i = 0;
	while (envp->next != NULL)
	{
		ft_putstr(envp->name);
		ft_putstr(envp->value);
		write(1, "\n", 1);
		envp = envp->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	env(envp);
// }