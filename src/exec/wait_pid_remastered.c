/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid_remastered.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:56:14 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/22 11:24:52 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	wait_pid_remastered(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_status_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_status_exit = 128 + WTERMSIG(status);
}
