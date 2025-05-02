/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/05/02 16:37:28 by dev              ###   ########.fr       */
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
			if (!pre_tokens)
				continue ;
			tokens = create_struct_tokens(pre_tokens);
			if (!check_syntax_errors(tokens))
				continue ;
			cmd = parser(tokens);
		}
		
		// fct exec
		// if (!strcmp(cmd->args[0], "echo"))
		// 	printf("cmd echo\n");
		// else if (!strcmp(cmd->args[0], "cd"))
		// 	printf("cmd cd\n");
		// else
		// 	printf("cmd inconne\n");

		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		

		
		t_cmd *current = cmd;
		while (current)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				if (!strcmp(current->args[0], "echo"))
				{
					int j = 1;
					while (current->args[j])
					{
						printf("%s ", current->args[j]);
						j++;
					}
					printf("\n");
					exit(0);
				}
				else
				{
					execvp(current->args[0], current->args);
					perror("execvp");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
			{
				int status;
				waitpid(pid, &status, 0);
			}
			else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			current = current->next;
		}

		
		
		// while (cmd->args[i])
		// {
		// 	printf("arg[%d] = %s\n", i, cmd->args[i]);
		// 	i++;
		// }
		// i = 0;
		// if (cmd->input_file)
		// 	printf("input: %s\n", cmd->input_file);
		// if (cmd->output_file)
		// 	printf("output: %s\n", cmd->output_file);


		
		// t_cmd *tmp = cmd;
		// int j = 0;

		// while (tmp)
		// {
		// 	printf("\n=== Commande %d ===\n", j);
		// 	i = 0;
		// 	while (tmp->args && tmp->args[i])
		// 	{
		// 		printf("arg[%d] = %s\n", i, tmp->args[i]);
		// 		i++;
		// 	}
		// 	if (tmp->input_file)
		// 		printf("input: %s\n", tmp->input_file);
		// 	if (tmp->output_file)
		// 		printf("output: %s (append = %d)\n", tmp->output_file, tmp->append);
		// 	tmp = tmp->next;
		// 	j++;
		// }

	}
	//supprimer historique a la fin ctrl c ?
	return (0);
}
