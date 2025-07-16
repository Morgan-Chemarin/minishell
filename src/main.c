/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/07/16 17:38:25 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_status_exit = 0;

int	count_unclosed_quotes(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && (!quote || quote == line[i]))
		{
			if (!quote)
				quote = line[i];
			else
				quote = 0;
		}
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

char	*read_full_line(void)
{
	char	*line;

	line = readline(GREEN "➜ " BLUE " minishell> " WHITE);
	if (!line)
		return (NULL);
	return (line);
}

void    siging_handler(int sig)
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
	(void)argc;
	(void)argv;
	char	*line;
	char	**pre_tokens;
	t_token	*tokens;
	t_env	*env;	
	t_cmd	*cmd;
	int		i;
	
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
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		if (count_unclosed_quotes(line))
		{
			ft_putstr("minishell: error: unclosed quote\n");
			free(line);
			continue;
		}
		add_history(line);
		pre_tokens = split_with_quote(line, env);
		if (!pre_tokens)
		{
			free(line);
			continue ;
		}
		tokens = create_struct_tokens(pre_tokens);
		if (!check_syntax_errors(tokens))
		{
			free(line);
			free(pre_tokens);
			continue ;
		}
		cmd = parser(tokens);
		if (cmd)
			exec_cmd(cmd, env, tokens, line);
	}
	return (0);
}
