/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/06/25 02:37:58 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	print_ascii_banner();
	while (1)
	{
		line = readline(GREEN "➜ " BLUE " minishell> " WHITE);
		if (!line)
			break ;
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		pre_tokens = split_with_quote(line);
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
			exec_cmd(cmd, env);
		// free all
	}
	//supprimer historique a la fin ctrl c ?
	return (0);
}
