/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:39:07 by dev               #+#    #+#             */
/*   Updated: 2025/09/30 18:44:04 by pibreiss         ###   ########.fr       */
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

int	process_heredoc_line(char **line, int expand, t_all *all)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_variables(*line, all->env, 1, all);
		free(*line);
		if (!expanded)
			return (0);
		*line = expanded;
	}
	return (1);
}

void	heredoc_loop(int write_fd, char *delimiter, int expand, t_all *all)
{
	char	*line;

	while (!g_interrupted)
	{
		line = readline("> ");
		if (!line || g_interrupted)
		{
			if (line)
				free(line);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (!process_heredoc_line(&line, expand, all))
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char	*delimiter, t_all *all)
{
	int		pipefd[2];
	char	*clean_delim;
	int		expand;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	expand = !is_quoted(delimiter);
	clean_delim = strip_quotes(delimiter);
	heredoc_loop(pipefd[1], clean_delim, expand, all);
	free(clean_delim);
	close(pipefd[1]);
	if (g_interrupted)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
