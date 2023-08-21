/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:48:22 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/17 15:38:11 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Returns a string representing the integer.
//Memory for sign + digits + '\0'.
//NULL if the allocation fails.
static char	*ft_create_string(long int number, int digits, long int divisor)
{
	char	*result;
	int		i;

	if (number == 0)
		return (ft_strdup("0"));
	result = malloc((digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (number < 0)
	{
		result[i++] = '-';
		digits--;
		number *= -1;
	}
	while (digits > 0)
	{
		result[i++] = ((number / divisor) % 10) + '0';
		divisor /= 10;
		digits--;
	}
	result[i] = '\0';
	return (result);
}

//counts the digits.
char	*ft_itoa(int n)
{
	int			digits;
	long int	divisor;
	long int	number;

	digits = 0;
	divisor = 1;
	number = n;
	while (number != number % divisor)
	{
		digits++;
		divisor *= 10;
	}
	if (number < 0)
		digits++;
	return (ft_create_string(number, digits, divisor / 10));
}
