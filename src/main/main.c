/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 19:07:04 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interrupted = 0;

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
	g_interrupted = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	init_all(t_all *all, char **envp)
{
	all->env = envp_to_list(envp);
	all->line = NULL;
	all->cmd_head = NULL;
	all->token = NULL;
	all->last_status_exit = 0;
	signal(SIGINT, siging_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	shell_loop(t_all *all)
{
	while (1)
	{
		all->line = read_full_line();
		if (g_interrupted)
		{
			all->last_status_exit = g_interrupted;
			g_interrupted = 0;
		}
		if (!all->line)
		{
			write(1, "exit\n", 5);
			return ;
		}
		if (!process_line(all->line, all))
			continue ;
		free_token(all->token);
		all->token = NULL;
		free_cmd(all->cmd_head);
		all->cmd_head = NULL;
		free(all->line);
		all->line = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Error: minishell must be in an interactive shell.\n", 2);
		return (1);
	}
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("Error: stdout is not a terminal.\n", 2);
		return (1);
	}
	init_all(&all, envp);
	shell_loop(&all);
	if (all.env)
		free_env(all.env);
	rl_clear_history();
	return (all.last_status_exit);
}
