/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_trim_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:04:09 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 22:23:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_process_string_to_trim(char *string, char *result, int *count,
				void (*copy_or_count)(char *, int *, char));
static void	ft_copy_value(char *new_value, char *value, int value_len,
				int expansion_case);

bool	ft_trim_value(char **string)
{
	char	*new_string;
	int		len;

	len = 0;
	if (!*string)
		return (true);
	ft_process_string_to_trim(*string, NULL, &len, ft_count_length);
	if (len == (int)ft_strlen(*string))
		return (true);
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (perror("malloc - trim variable value"), false);
	new_string[len] = '\0';
	ft_process_string_to_trim(*string, new_string, NULL, ft_copy_char);
	free(*string);
	*string = new_string;
	return (true);
}

static void	ft_process_string_to_trim(char *string, char *result, int *count,
				void (*copy_or_count)(char *, int *, char))
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			copy_or_count(result + j++, count, ' ');
		if (string[i])
			copy_or_count(result + j++, count, string[i++]);
	}
}

bool	protect_value(char **value, int expansion_case)
{
	char	*new_value;
	int		value_len;

	if (!*value)
		return (true);
	value_len = ft_strlen(*value);
	if (expansion_case == v_trim)
		value_len += 2;
	else if (expansion_case == v_no_trim)
		value_len += 3;
	new_value = ft_calloc(value_len + 1, sizeof(char));
	if (!new_value)
		return (perror("error - adding quotes to value in expansion"), false);
	ft_copy_value(new_value, *value, value_len, expansion_case);
	ft_free_ptr_and_set_to_null((void **)value);
	*value = new_value;
	return (true);
}

static void	ft_copy_value(char *new_value, char *value, int value_len,
				int expansion_case)
{
	new_value[0] = '\"';
	if (expansion_case == v_trim)
	{
		ft_strlcat(new_value, value, value_len + 1);
		new_value[value_len - 1] = '\"';
	}
	else if (expansion_case == v_no_trim)
	{
		new_value[1] = '\"';
		ft_strlcat(new_value, value, value_len + 1);
	}
}
