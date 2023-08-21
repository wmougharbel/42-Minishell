/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create_name_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:34:55 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 00:55:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_create_name(char *argument, char **name,
				char *position_of_equal_sign);
static bool	ft_create_value(char **value, char *position_of_equal_sign);

bool	ft_create_name_and_value(char *argument, char **name,
	char **value, bool *print_empty_quotes)
{
	char	*position_of_equal_sign;

	*print_empty_quotes = false;
	position_of_equal_sign = ft_strchr(argument, '=');
	if (position_of_equal_sign)
		*print_empty_quotes = true;
	if (!ft_create_name(argument, name, position_of_equal_sign))
		return (false);
	if (!ft_create_value(value, position_of_equal_sign))
		return (ft_free_ptr_and_set_to_null((void **)name), false);
	return (true);
}

static bool	ft_create_name(char *argument, char **name,
			char *position_of_equal_sign)
{
	*name = NULL;
	if (!position_of_equal_sign)
	{
		*name = ft_strdup(argument);
		if (!*name)
			return (perror("error creating name in store_env"), false);
		return (true);
	}
	else
	{
		*name = ft_substr(argument, 0, position_of_equal_sign - argument);
		if (!*name)
			return (perror("error creating name in store_env"), false);
	}
	return (true);
}

static bool	ft_create_value(char **value, char *position_of_equal_sign)
{
	int	value_len;

	*value = NULL;
	value_len = 0;
	if (!position_of_equal_sign)
		return (true);
	value_len = ft_strlen(position_of_equal_sign + 1);
	if (value_len == 0)
		return (true);
	*value = ft_substr(position_of_equal_sign, 1, value_len);
	if (!*value)
		return (perror("error creating env value"), false);
	return (true);
}
