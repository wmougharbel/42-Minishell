/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:37:14 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 15:37:34 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_check_file(char *command, t_shell_data *shell_data)
{
	if (!ft_is_file_existent(command, shell_data))
		return (false);
	if (ft_is_directory(command, shell_data))
		return (false);
	if (!ft_is_executable(command, shell_data))
		return (false);
	return (true);
}
