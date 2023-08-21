/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:33:18 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:57:50 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//finds the last occurence of c (as char) in string *s including '\0'.
//returns address of occurence else NULL.
//stores the address of occurence in location.
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*pointer;
	char	*location;

	pointer = (char *)s;
	location = NULL;
	i = -1;
	while (pointer[++i] != '\0')
		if (pointer[i] == (char)c)
			location = &pointer[i];
	if (pointer[i] == (char)c)
		return (&pointer[i]);
	return (location);
}
