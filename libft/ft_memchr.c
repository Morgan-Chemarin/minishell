/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:14:13 by mchemari          #+#    #+#             */
/*   Updated: 2024/11/08 09:54:49 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p;
	unsigned char		ch;

	i = 0;
	p = (const unsigned char *)s;
	ch = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (p[i] == ch)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
