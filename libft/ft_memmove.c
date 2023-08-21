/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:35:18 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:25 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copys "n" bytes from src to dst.
//returns dst.
//typecast so the system knows how big one byte is.
//dst before source -> start at the beginning.
//dst after source start at the end -> so in case of overlap no value gest lost
//before copied to dst.
//src is'nt alwas the same as in the beginning when overlapping.
//start with len-- so the null character wont get copied.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	i = -1;
	if (dst < src && (p1 != NULL || p2 != NULL))
	{
		while (++i < len)
			p1[i] = p2[i];
	}
	else if (p1 != NULL || p2 != NULL)
	{
		while (len > 0)
		{
			len--;
			p1[len] = p2[len];
		}
	}
	return (dst);
}
