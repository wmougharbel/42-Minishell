/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:47:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/03 22:24:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_quotes_in_delimiter(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_is_char_quote(string[i]))
			return (true);
		i++;
	}
	return (false);
}
