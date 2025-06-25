/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:02:02 by mchemari          #+#    #+#             */
/*   Updated: 2025/06/25 16:02:31 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *source)
{
	char	*array;
	size_t	i;

	array = malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (source[i])
	{
		array[i] = source[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
