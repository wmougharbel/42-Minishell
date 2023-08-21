/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:05:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/30 19:33:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterates ’lst’ and applies the function ’f’ on the content of each node.
// Creates a new list resulting of the successive applications of 'f'.
// The ’del’ function is used to delete the content of a node if needed.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_src;
	t_list	*result;
	t_list	*lst_res;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	lst_src = lst;
	result = NULL;
	while (lst_src != NULL)
	{
		lst_res = malloc(sizeof(t_list));
		if (lst_res == NULL)
			return (ft_lstclear(&result, del), NULL);
		lst_res->next = NULL;
		lst_res->content = f(lst_src->content);
		ft_lstadd_back(&result, lst_res);
		if (!lst_res->content)
			return (ft_lstclear(&result, del), NULL);
		lst_src = lst_src->next;
	}
	return (result);
}
