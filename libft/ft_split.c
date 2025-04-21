/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:10:41 by mchemari          #+#    #+#             */
/*   Updated: 2024/11/15 11:59:02 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_word(char const *s, char c, int i)
{
	if (s[i] != c && (i == 0 || s[i - 1] == c))
		return (1);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_word(s, c, i))
			count++;
		i++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *index)
{
	int		start;
	int		end;
	char	*word;

	while (s[*index] && s[*index] == c)
		(*index)++;
	start = *index;
	while (s[*index] && s[*index] != c)
		(*index)++;
	end = *index;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, (char *)&s[start], end - start + 1);
	return (word);
}

static int	fill_words(char **result, char const *s, char c, int words)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < words)
	{
		result[i] = get_word(s, c, &index);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			return (0);
		}
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	if (!fill_words(result, s, c, words))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
