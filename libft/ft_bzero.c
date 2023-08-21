/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:42:52 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:48:10 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//writes "n" zeroed bytes to the byte string *s.
//typecast so the system knows how big one byte is.
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*pointer;

	pointer = (unsigned char *)s;
	i = 0;
	while (i < n)
		pointer[i++] = '\0';
}
