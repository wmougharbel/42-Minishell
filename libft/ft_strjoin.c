/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:45:06 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:51:07 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns NULL if malloc fails.
//else returns a new string (s1 + s2).
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_length;
	char	*new_string;
	int		i;
	int		j;

	total_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc((total_length + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		new_string[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		new_string[j++] = s2[i++];
	new_string[j] = '\0';
	return (new_string);
}
