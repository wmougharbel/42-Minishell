/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:28:25 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:57:46 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//locates the first occurence of the null-terminated string needle in 
//null-terminated string haystack where "len" characters of haystack
//are searched. Returns the address of the occurence.
//if len < strlen(needle) -> needle cant be found.
//if strncmp returns 0 -> everthing matches for "n" characters.
//no or empty needle in input -> return haystack.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	length_needle;

	i = 0;
	length_needle = ft_strlen(needle);
	if (needle == NULL || *needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0' && length_needle <= len - i)
	{
		if (haystack[i] == *needle)
		{
			if (ft_strncmp((haystack + i), needle, length_needle) == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
