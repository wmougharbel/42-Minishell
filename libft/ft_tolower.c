/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:30:58 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:58:03 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns the corresponding lowercase letter
//else value reamains unchanged
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
