/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:53:10 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copys "n" bytes from src to dst.
//behavior undefined if they overlap.
//returns dst.
//typecast so the system knows how big one byte is.
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (dst == NULL && src == NULL)
		return (dst);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	i = -1;
	while (++i < n)
		p1[i] = p2[i];
	return (dst);
}
