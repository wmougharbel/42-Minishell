/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:23 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/04 10:46:49 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **pwd, bool print)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (pwd)
		*pwd = path;
	if (!path)
	{
		ft_putstr_fd("minishell: path doesn't exist\n", 2);
		return (__mini_error);
	}
	if (print)
		ft_print_pwd_and_free(path);
	return (__success);
}

void	ft_print_pwd_and_free(char *path)
{
	printf("%s\n", path);
	free(path);
}
