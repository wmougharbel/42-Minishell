/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:35:23 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:49:33 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns the addres of the last node in the list.
//saves the addres in temp and returns it once the while ends.
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;
	t_list	*last;

	tmp = lst;
	last = lst;
	while (tmp != NULL)
	{
		last = tmp;
		tmp = tmp->next;
	}
	return (last);
}
