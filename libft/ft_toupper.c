/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:06:51 by cmenke            #+#    #+#             */
/*   Updated: 2022/12/30 12:58:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns the corresponding uppercase letter
//else value reamains unchanged
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
