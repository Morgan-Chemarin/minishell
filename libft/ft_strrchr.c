/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:46:49 by mchemari          #+#    #+#             */
/*   Updated: 2024/11/07 13:14:47 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	strlen;

	i = 0;
	strlen = 0;
	while (s[strlen])
		strlen++;
	i = strlen;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i--;
	}
	if ((char)c == '\0')
		return (&s[strlen]);
	return (NULL);
}
