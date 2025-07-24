/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:05:22 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:52:06 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr(env->name);
			write(1, "=", 1);
			ft_putstr(env->value);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
