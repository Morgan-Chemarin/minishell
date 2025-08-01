/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:29 by pibreiss          #+#    #+#             */
/*   Updated: 2025/07/24 08:52:27 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void    free_all(t_cmd *cmd, t_token *token, t_env *env, char *line)
{
	if (cmd)
		free_cmd(cmd);
	if (env)
		free_env(env);
    if (token)
		free_token(token);
    if (line)
		free(line);
    rl_clear_history();
}

void    ft_exit(t_cmd *cmd, t_token *token, t_env *env, char *line)
{
    int		i;
    int		code;
	int		tty_fd;

    i = 0;
    tty_fd = open("/dev/tty", O_WRONLY);
    if (tty_fd >= 0)
    {
        write(tty_fd, "exit\n", 5);
    }
    else
        write(STDOUT_FILENO, "exit\n", 5);
    if (count_arg(cmd->args) == 1)
    {
        free_all(cmd, token, env, line);
        close(tty_fd);
        exit(1);
    }
    else if (count_arg(cmd->args) == 2)
    {
        while (cmd->args[1][i])
        {
            if (!(cmd->args[1][i] >= '0' && cmd->args[1][i] <= '9')
                && cmd->args[1][i] != '-')
            {
                free_all(cmd, token, env, line);
                write(tty_fd, "exit: numeric argument required\n", 32);
                close(tty_fd);
                exit(2);
            }
            i++;
        }
        code = ft_atoi(cmd->args[1]);
        free_all(cmd, token, env, line);
        exit(code);
        close(tty_fd);
    }
    else if (count_arg(cmd->args) > 2)
        write(tty_fd, "exit: too many arguments\n", 25);
    close(tty_fd);
}
