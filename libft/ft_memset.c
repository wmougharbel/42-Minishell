/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:41:08 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:29 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//fills the byte string *b with c(as unsigned char) for len bytes.
//returns its first argument *b.
//typecast so the system knows how big one byte is.
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pointer;

	pointer = (unsigned char *)b;
	i = 0;
	while (i < len)
		pointer[i++] = c;
	return (b);
}
