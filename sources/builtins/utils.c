/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 00:15:51 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_find_env_variable(char *variable_name, t_list *env_list)
{
	t_env	*one_env_variable;

	if (!variable_name || !env_list)
		return (NULL);
	while (env_list)
	{
		one_env_variable = (t_env *)env_list->content;
		if (!ft_strcmp(one_env_variable->name, variable_name))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	ft_free_name_and_value(char **name, char **value)
{
	ft_free_ptr_and_set_to_null((void **)name);
	ft_free_ptr_and_set_to_null((void **)value);
}

bool	ft_get_current_working_directory(char **cwd_buf)
{
	*cwd_buf = ft_calloc(MAXPATHLEN + 1, sizeof(char));
	if (!*cwd_buf)
		return (perror("error creating cwd_buf"), false);
	if (!getcwd(*cwd_buf, MAXPATHLEN))
		return (free(*cwd_buf), perror("error getting cwd"), false);
	return (true);
}
