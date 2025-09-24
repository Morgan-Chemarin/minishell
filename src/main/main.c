/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/09/24 11:25:41 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_last_status_exit = 0;
int	g_interrupted = 0;

char	*read_full_line(void)
{
	char	*line;

	line = readline(GREEN "➜ " BLUE " minishell> " WHITE);
	if (!line)
		return (NULL);
	return (line);
}

void siging_handler(int sig)
{
    (void)sig;
    g_interrupted = 130;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	// char	*line;
	// t_env	*env;

	(void)argc;
	(void)argv;
	all.env = envp_to_list(envp);
    all.line = NULL;
    all.cmd_head = NULL;
    all.token = NULL;
    all.heredoc_fd = -1;
    all.last_status_exit = 0;
	signal(SIGINT, siging_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		all.line = read_full_line();
		if (!all.line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!process_line(all.line, &all.env, &all))
			continue ;
		free(all.line);
		if (g_interrupted)
		{
			all.last_status_exit = g_interrupted;
			g_interrupted = 0;
		}
	}
	if (all.env)
		free_env(all.env);
	rl_clear_history();
	return (all.last_status_exit);
}
