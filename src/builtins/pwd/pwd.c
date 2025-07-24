/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:29:57 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:53:10 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	else
	{
		ft_putstr(cwd);
		write(1, "\n", 1);
		free(cwd);
	}
	return (0);
}
