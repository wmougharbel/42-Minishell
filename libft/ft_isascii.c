/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:17:35 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:48:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// checks if the character is part of ascii (0 - 127).
// returns non-zero for true and 0 for false.
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
