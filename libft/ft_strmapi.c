/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:02:33 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:51:22 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Applies the function ’f’ to each character of the
//string ’s’. 'f' takes the index of the char as first argument.
//creates new string with malloc resulting from successive applications of ’f’.
//f calls the function stored there since it holds the addres of it,
//then it will do its actions and returns the new value.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	i = -1;
	result = ft_strdup(s);
	while (s[++i] != '\0' && result != NULL)
		result[i] = f(i, s[i]);
	return (result);
}
