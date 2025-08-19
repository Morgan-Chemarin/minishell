/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/08/19 10:25:37 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_status_exit = 0;

char	*read_full_line(void)
{
	char	*line;

	line = readline(GREEN "➜ " BLUE " minishell> " WHITE);
	if (!line)
		return (NULL);
	return (line);
}

void	siging_handler(int sig)
{
	(void)sig;
	write(130, "^C", 2);
	write(1, "\n", 1);
	g_last_status_exit = 130;
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
		if (!process_line(line, env))
			continue ;
		free(line);
	}
	if (env)
		free_env(env);
	rl_clear_history();
	return (g_last_status_exit);
}
