/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:32:34 by dev               #+#    #+#             */
/*   Updated: 2025/06/19 00:11:42 by dev              ###   ########.fr       */
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
	// t_env	*env;	
	// t_env	*head;	
	t_cmd	*cmd;
	// int		i;

	(void)envp;
	// i = 0;
	while (1)
	{
		line = readline(BLUE "minishell> " GREEN);
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
			exec_cmd(cmd);
			// check_args_builtin(); // fonction verifier l'ordre et la validité des argus pour une fonction builtin
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
	}
	//supprimer historique a la fin ctrl c ?
	return (0);
}


	// env = new_env();
		// head = env;

		// while (envp[i])
		// {
		// 	env->name = ft_strdup(envp[i]); // fonction split =
		// 	if (envp[i + 1])
		// 	{
		// 		env->next = new_env();
		// 		env = env->next;
		// 	}
		// 	i++;
		// }

		

		// env = head;

		// while (env)
		// {
		// 	printf("%s\n", env->name);
		// 	env = env->next;
		// }

	
		// t_cmd *current = cmd;
		// while (current)
		// {
		// 	pid_t pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		if (!strcmp(current->args[0], "echo"))
		// 		{
		// 			echo(current);
		// 			exit(0);
		// 		}
		// 		else
		// 		{
		// 			execvp(current->args[0], current->args);
		// 			perror("execvp");
		// 			exit(EXIT_FAILURE);
		// 		}
		// 	}
		// 	else if (pid > 0)
		// 	{
		// 		int status;
		// 		waitpid(pid, &status, 0);
		// 	}
		// 	else
		// 	{
		// 		perror("fork");
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	current = current->next;
		// }

		
		
		


		
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

// exec_cmd
		// t_cmd	*tmp = cmd;
		// 	while (tmp)
		// 	{
		// 		if (tmp->type == CMD_BUILTNS)
		// 		{
		// 			if (check_builtins_args(tmp))
		// 			{
		// 				printf("la syntaxe est  pas good\n");
		// 				break;
		// 			}
		// 		}
		// 		tmp = tmp->next;
		// 	}