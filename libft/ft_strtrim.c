/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:59:06 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:57:54 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns NULL if malloc fails.
//else returns a copy of "s1" where characters from "set" are removed
//from the beginning and the end. (order doesn't matter in set).
//Check with strchr in "set" for a match. At start and end of "s1".
char	*ft_strtrim(char const *s1, char const *set)
{
	int	len_res;

	if (*s1 == '\0')
		return (ft_strdup(""));
	len_res = ft_strlen(s1);
	if (*set == '\0')
		return (ft_substr(s1, 0, len_res));
	while (ft_strchr(set, *s1) != NULL && len_res > 0)
	{
		s1++;
		len_res--;
	}
	while (ft_strchr(set, *(s1 + len_res - 1)) != NULL && len_res > 0)
		len_res--;
	return (ft_substr(s1, 0, len_res));
}
