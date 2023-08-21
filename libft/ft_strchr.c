/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:33:18 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 14:26:40 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//finds the first occurence of c (as char) in string *s including '\0'.
//returns address of occurence else NULL.
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*pointer;

	pointer = (char *)s;
	i = -1;
	while (pointer[++i] != '\0')
		if (pointer[i] == (char)c)
			return (&pointer[i]);
	if (pointer[i] == (char)c)
		return (&pointer[i]);
	return (NULL);
}
