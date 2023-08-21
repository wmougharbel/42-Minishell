/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:51:17 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 14:29:02 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//deletes the content with function del.
//then frees the complete node except for next.
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}
