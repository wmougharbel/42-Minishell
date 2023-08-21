/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_char_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:43:42 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/04 11:31:04 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_env_list_to_envp_array(t_shell_data *shell_data)
{
	t_list		*env_list;
	t_env		*env_variable;
	int			i;

	i = 0;
	env_list = shell_data->env_list;
	shell_data->envp_array = ft_calloc(ft_lstsize(env_list) + 1,
			sizeof(char *));
	if (!shell_data->envp_array)
		return (perror("error creatin envp array"), false);
	while (env_list)
	{
		env_variable = (t_env *)env_list->content;
		shell_data->envp_array[i] = ft_create_one_env_variable(env_variable);
		if (!shell_data->envp_array[i])
			return (false);
		i++;
		env_list = env_list->next;
	}
	return (true);
}

char	*ft_create_one_env_variable(t_env *one_variable)
{
	char	*env_variable;
	char	*name_and_equal_sign;

	name_and_equal_sign = NULL;
	env_variable = NULL;
	name_and_equal_sign = ft_strjoin(one_variable->name, "=");
	if (!name_and_equal_sign)
		return (perror("error creating env name_and_equal_sign"), NULL);
	if (one_variable->value)
	{
		env_variable = ft_strjoin(name_and_equal_sign, one_variable->value);
		free(name_and_equal_sign);
		if (!env_variable)
			return (perror("error creating env_variable"), NULL);
		return (env_variable);
	}
	return (name_and_equal_sign);
}
