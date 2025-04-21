/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:53:04 by mchemari          #+#    #+#             */
/*   Updated: 2024/11/15 11:57:59 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	max_size;

	max_size = -1;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size > max_size / nmemb)
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, nmemb * size);
	return (tab);
}
