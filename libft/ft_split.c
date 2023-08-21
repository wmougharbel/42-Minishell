/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:06:57 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:50:51 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//counts the substrings and multiple occurences of delimiter are ignored
//break to prevent from reading over '\0'.
static int	ft_count(char const *s, char c)
{
	int	i;
	int	substrings;

	i = -1;
	substrings = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			substrings++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				break ;
		}
	}
	return (substrings);
}

//splits the strings and frees the created ones,
//if an error occurs during the process.
//else returns the splitted strings.
static char	**ft_split_strings(char **result, char const *s, char c, int j)
{
	int	start;
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			result[j] = ft_substr(s, start, i - start);
			if (result[j++] == NULL)
			{
				while (--j >= 0)
					free(result[j]);
				free(result);
				return (NULL);
			}
			if (s[i] == '\0')
				break ;
		}
	}
	result[j] = NULL;
	return (result);
}

//returns an array of strings obtained by splitting ’s’ using the
//character ’c’ as a delimiter.
//array ends with a NULL pointer.
//returns NULL if the allocation fails.
char	**ft_split(char const *s, char c)
{
	char	**result;

	result = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (ft_split_strings(result, s, c, 0));
}
