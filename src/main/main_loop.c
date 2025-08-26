/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:15:52 by dev               #+#    #+#             */
/*   Updated: 2025/08/26 15:15:07 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_empty_or_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (0);
	}
	if (count_unclosed_quotes(line))
	{
		ft_putstr("minishell: error: unclosed quote\n");
		free(line);
		return (0);
	}
	return (1);
}

int	process_line(char *line, t_env **env)
{
	char	**pre_tokens;
	t_token	*tokens;
	t_cmd	*cmd;

	if (!handle_empty_or_quotes(line))
		return (0);
	add_history(line);
	pre_tokens = split_with_quote(line, *env);
	if (!pre_tokens)
		return (0);
	tokens = create_struct_tokens(pre_tokens);
	free_array_str(pre_tokens);
	if (!check_syntax_errors(tokens))
	{
		g_last_status_exit = 2;
		return (free_token(tokens), 0);
	}
	cmd = parser(tokens, *env);
	if (cmd)
		exec_cmd(cmd, env, tokens, line);
	if (cmd)
		free_cmd(cmd);
	if (tokens)
		free_token(tokens);
	return (1);
}
