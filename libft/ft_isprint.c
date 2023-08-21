/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:17:35 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:48:20 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// checks if the character is printable (32 - 126).
// returns non-zero for true and 0 for false.
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
