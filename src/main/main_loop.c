/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:15:52 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 19:05:57 by mchemari         ###   ########.fr       */
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
		return (0);
	if (count_unclosed_quotes(line))
	{
		ft_putstr("minishell: error: unclosed quote\n");
		return (0);
	}
	return (1);
}

static t_cmd	*parse_line(char *line, t_all *all)
{
	char	**pre_tokens;
	t_token	*tokens;
	t_cmd	*cmd;

	if (!handle_empty_or_quotes(line))
		return (NULL);
	add_history(line);
	pre_tokens = split_with_quote(line, all);
	if (!pre_tokens)
	{
		free(line);
		return (NULL);
	}
	tokens = create_struct_tokens(pre_tokens);
	free_array_str(pre_tokens);
	if (!check_syntax_errors(tokens))
	{
		all->last_status_exit = 2;
		free_token(tokens);
		return (NULL);
	}
	all->token = tokens;
	cmd = parser(tokens, all);
	return (cmd);
}

int	process_line(char *line, t_all *all)
{
	t_cmd	*cmd;

	cmd = parse_line(line, all);
	if (!cmd)
	{
		if (all->token)
		{
			free_token(all->token);
			all->token = NULL;
		}
		free(line);
		return (0);
	}
	all->line = line;
	all->cmd_head = cmd;
	exec_cmd(cmd, all);
	return (1);
}
