/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:17:35 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:48:15 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//checks if the character is (‘A’ - ‘Z’) or (‘a’ – ‘z’).
//returns non-zero for true and 0 for false.
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
