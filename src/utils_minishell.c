/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:36:06 by pibreiss          #+#    #+#             */
/*   Updated: 2025/06/25 03:00:14 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// char	*ft_strdup(char *source)
// {
// 	char	*array;
// 	size_t	i;

// 	array = malloc(sizeof(char) * (ft_strlen(source) + 1));
// 	if (array == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (source[i])
// 	{
// 		array[i] = source[i];
// 		i++;
// 	}
// 	array[i] = '\0';
// 	return (array);
// }

// int	ft_atoi(char *str)
// {
// 	int				i;
// 	unsigned long	result;
// 	int				sign;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) ||str[i] == ' ')
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		if (result > 9223372036854775807 && (sign == -1))
// 			return (0);
// 		if (result > 9223372036854775807 && (sign == 1))
// 			return (-1);
// 		result = result * 10 + (str[i] - 48);
// 		i++;
// 	}
// 	return (result * sign);
// }
