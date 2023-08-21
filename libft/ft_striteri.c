/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:52:26 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:51:02 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Applies the function ’f’ on each character of the string passed as argument.
// 'f' takes the index of char as first argument.
// Each character is passed by address to ’f’ to be modified if necessary.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
		f(i, &s[i]);
}
