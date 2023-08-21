/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:21:02 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 01:28:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//compares byte strings s1 and s2 for "n" bytes assuming both are n long.
//returns difference (s1 - s2) or 0 if no difference.
//The comparison is done using unsigned char.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*string1;
	unsigned char	*string2;

	i = 0;
	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (string1[i] == string2[i] && i + 1 < n)
		i++;
	return ((unsigned char)string1[i] - (unsigned char)string2[i]);
}
