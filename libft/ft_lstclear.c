/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:38:15 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:49:13 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//deletes content, frees the node and sets the start pointer (*lst) to NULL.
//repeats for complete chain of nodes.
//checks if del is not NULL.
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	tmp = *lst;
	if (del != NULL)
	{
		while (tmp != NULL)
		{
			*lst = tmp;
			tmp = tmp->next;
			ft_lstdelone(*lst, del);
		}
	}
	*lst = NULL;
}
