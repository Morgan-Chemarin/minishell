/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:24:12 by mchemari          #+#    #+#             */
/*   Updated: 2024/11/13 11:48:22 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		cmpt;

	cmpt = 0;
	current = lst;
	while (current != NULL)
	{
		cmpt++;
		current = current->next;
	}
	return (cmpt);
}
