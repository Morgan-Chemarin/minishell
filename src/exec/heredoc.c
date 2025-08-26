/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:39:07 by dev               #+#    #+#             */
/*   Updated: 2025/08/25 11:16:03 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"'))
		return (1);
	return (0);
}

char	*strip_quotes(char *s)
{
	int		len;
	char	*res;

	if (!is_quoted(s))
		return (ft_strdup(s));
	len = ft_strlen(s);
	res = ft_substr(s, 1, len - 2);
	return (res);
}

void	heredoc_loop(int write_fd, char *delimiter, int expand, t_env *env)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			if (line)
				free(line);
			break ;
		}
		if (expand)
		{
			expanded = expand_variables(line, env, 1);
			free(line);
			if (!expanded)
				break ;
			line = expanded;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char	*delimiter, t_env *env)
{
	int		pipefd[2];
	char	*clean_delim;
	int		expand;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	expand = !is_quoted(delimiter);
	clean_delim = strip_quotes(delimiter);
	heredoc_loop(pipefd[1], clean_delim, expand, env);
	free(clean_delim);
	close(pipefd[1]);
	return (pipefd[0]);
}
