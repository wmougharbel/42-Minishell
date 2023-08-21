/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:41:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 01:57:46 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//starts with "SHELL_NAME: " and ends with a newline
void	ft_print_error_message(char *part1, char *part2,
			char *part3, char *part4)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (part1)
		ft_putstr_fd(part1, 2);
	if (part2)
		ft_putstr_fd(part2, 2);
	if (part3)
		ft_putstr_fd(part3, 2);
	if (part4)
		ft_putstr_fd(part4, 2);
	ft_putstr_fd("\n", 2);
}
