/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/09/23 16:49:05 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_status_exit = 0;
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
	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = envp_to_list(envp);
	signal(SIGINT, siging_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = read_full_line();
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!process_line(line, &env))
			continue ;
		free(line);
		if (g_interrupted)
		{
			g_last_status_exit = g_interrupted;
			g_interrupted = 0;
		}
	}
	if (env)
		free_env(env);
	rl_clear_history();
	return (g_last_status_exit);
}
