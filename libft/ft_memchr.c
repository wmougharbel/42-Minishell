/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:41:37 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:10 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//locate byte in byte string
//finds the first occurence of c (as unsigned char) in "n" bytes 
//including '\0' or even over the terminator.
//returns the address of the occurence else NULL.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pointer;
	size_t			i;

	pointer = (unsigned char *)s;
	i = -1;
	while (++i < n)
		if (pointer[i] == (unsigned char)c)
			return (&pointer[i]);
	return (NULL);
}
