/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_get_name_value.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:22:02 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 22:22:55 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//start at 1 && len -1 for the dollar removal
bool	ft_get_variable_name(char *string, char **variable_name)
{
	int		i;
	char	*delimiters;

	delimiters = " \t\n$?\"\'=[]()";
	i = 1;
	while (string[i] && !ft_strchr(delimiters, string[i]))
		i++;
	if (i == 1)
		return (true);
	*variable_name = ft_substr(string, 1, i - 1);
	if (!variable_name)
		return (perror("error creating variable_name"), false);
	return (true);
}

bool	ft_get_variable_value(char *name, char **value, t_list *env_list)
{
	t_list	*variable_node;

	if (!name)
		return (true);
	variable_node = ft_find_env_variable(name, env_list);
	if (variable_node)
	{
		if (((t_env *)variable_node->content)->value)
		{
			*value = ft_strdup(((t_env *)variable_node->content)->value);
			if (!*value)
				return (perror("error creating value"), false);
		}
	}
	return (true);
}

bool	ft_get_exit_code_string(char **name, char **value,
			t_shell_data *shell_data)
{
	*value = ft_itoa(shell_data->exit_code);
	*name = ft_strdup("?");
	if (!*name || !*value)
		return (perror("error creating exit_code string"), false);
	return (true);
}
