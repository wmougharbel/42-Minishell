/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:13:09 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:48:08 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//searches for isspace(3) then for signs (one only),
//then numbers. if no number is found in pattern returns 0.
//else returns the found integer.
int	ft_atoi(const char *str)
{
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			minus = -1;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	return (result * minus);
}
