/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:54:36 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:51:14 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copies up to dstsize - 1 characters from the string src to 
//dst, NUL-terminating the result if dstsize is not 0.
//returns the total length of the string they tried to create. 
//For strlcpy() that means the length of src.
//If the src and dst strings overlap, the behavior is undefined.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while ((src[i] != '\0') && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0 && dst != NULL)
		dst[i] = '\0';
	return (ft_strlen(src));
}
