/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:06:51 by dev               #+#    #+#             */
/*   Updated: 2025/06/18 16:47:09 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    exec_cmd(t_cmd *cmd)
{
    t_cmd   *tmp;

    tmp = cmd;
    while (tmp)
    {
        if (tmp->type == CMD_BUILTNS)
        {
            if (!check_builtins_args(tmp))
                return ;
            printf("ya pas la fonction mais elle est reocnnu est bonne challah\n");
            //appel buitlins une fois que la syntaxe des symboles est good + syntaxe de la collande 
        }
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(cmd->args[0], cmd->args);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
            else
                waitpid(pid, NULL, 0);

            printf("fct execv\n");
            //appel execv
        }
        tmp = tmp->next;
    }
}