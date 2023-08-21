/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:21:58 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns a pointer to a new string which is a duplicate of the string s.
//NULL if allocation fails.
char	*ft_strdup(const char *s)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}
