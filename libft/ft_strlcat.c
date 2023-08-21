/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:10:03 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 14:27:07 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies (dstsize-strlen(dst)-1) and returns strlen of (initial dst + src)
// size is equal to the complete size of dst -> dst[size]
// strlen_dst is to remember the original length of dst.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	strlen_dst;
	size_t	strlen_src;
	size_t	i;

	strlen_dst = ft_strlen(dst);
	strlen_src = ft_strlen(src);
	if (dstsize == 0)
		return (strlen_src);
	if (strlen_dst > dstsize)
		return (dstsize + strlen_src);
	i = -1;
	while (src[++i] != '\0' && strlen_dst + i + 1 < dstsize)
		dst[strlen_dst + i] = src[i];
	dst[strlen_dst + i] = '\0';
	return (strlen_dst + strlen_src);
}
