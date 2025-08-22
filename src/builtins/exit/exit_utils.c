/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:57:32 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/22 11:24:29 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_overflow(long long num, int sign, char c)
{
	unsigned long long	limit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	if (num > (long long)(limit / 10))
		return (0);
	if (num == (long long)(limit / 10) && (c - '0') > (int)(limit % 10))
		return (0);
	return (1);
}

int	is_valid_long_long(char *str)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (!check_overflow(num, sign, str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}
