/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/04/22 14:01:23 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	char	**pre_tokens;
	t_token	*tokens;
	t_cmd	*cmd;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		else {
			add_history(line);
			pre_tokens = split_with_quote(line); // fusinner en une fctn
			tokens = create_struct_tokens(pre_tokens);
			if (!check_syntax_errors(tokens))
				continue ;
			cmd = parser(tokens);
		}
		while (cmd->args[i])
		{
			printf("arg[%d] = %s\n", i, cmd->args[i]);
			i++;
		}
		i = 0;
		if (cmd->input_file)
			printf("input: %s\n", cmd->input_file);
		if (cmd->output_file)
			printf("output: %s\n", cmd->output_file);
	}
	//supprimer historique a la fin ctrl c ?
	return (0);
}
