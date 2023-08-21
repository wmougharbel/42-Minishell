/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:18 by npavelic          #+#    #+#             */
/*   Updated: 2023/08/04 20:06:00 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_lines(int i, char **str);

void	ft_echo(char **command)
{
	int		i;
	int		j;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (command[i] && command[i][0] == '-'
		&& command[i][1] == 'n')
	{
		j = 1;
		while (command[i][j] == 'n')
			j++;
		if (command[i][j] == '\0')
			n_flag = true;
		else
			break ;
		i++;
	}
	print_lines(i, command);
	if (n_flag == false)
		printf("\n");
}

static void	print_lines(int i, char **str)
{
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
}
