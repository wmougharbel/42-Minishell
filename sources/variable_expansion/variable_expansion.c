/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:32:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 22:18:54 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_expand_one_variable(int exp_case, char **string,
				char **token, t_shell_data *shell_data);
static int	ft_get_expansion_case(char **string, bool in_double_quotes);
static bool	ft_replace_name_with_value(char **string, char **token,
				char *variable_name, char *variable_value);

bool	ft_expand_variables_in_tokens(t_list **tokens, t_shell_data *shell_data)
{
	t_list		*previous;
	t_list		*current;
	t_list		*next;

	previous = NULL;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (!ft_expand_variables_in_string(
				&((t_tokens *)current->content)->token, shell_data, false))
			return (ft_putendl_fd("error - variable expansion", 2), false);
		if (!ft_strcmp(((t_tokens *)current->content)->token, ""))
			ft_cut_out_node(tokens, previous, current, next);
		else
			previous = current;
		current = next;
	}
	return (true);
}

bool	ft_expand_variables_in_string(char **string, t_shell_data *shell_data,
				bool ignore_quotes)
{
	char	*moving_string;
	bool	in_double_quotes;
	bool	in_single_quotes;
	int		exp_case;

	moving_string = *string;
	in_double_quotes = false;
	in_single_quotes = false;
	while (*moving_string)
	{
		if (!ignore_quotes)
			ft_update_quote_state(&in_single_quotes,
				&in_double_quotes, *moving_string);
		if (*moving_string == '$' && !in_single_quotes)
		{
			exp_case = ft_get_expansion_case(&moving_string,
					in_double_quotes);
			if (!ft_expand_one_variable(exp_case, &moving_string,
					string, shell_data))
				return (false);
		}
		if (*moving_string)
			moving_string += 1;
	}
	return (true);
}

static bool	ft_expand_one_variable(int exp_case, char **string,
			char **token, t_shell_data *shell_data)
{
	char	*name;
	char	*value;
	bool	error;

	name = NULL;
	value = NULL;
	error = false;
	if (exp_case == v_exit_code || exp_case == v_trim || exp_case == v_no_trim)
	{
		if (!ft_get_variable_name(*string, &name))
			error = true;
		else if (!ft_get_variable_value(name, &value, shell_data->env_list))
			error = true;
		else if (exp_case == v_trim && !ft_trim_value(&value))
			error = true;
		else if (!shell_data->add_no_quotes && !protect_value(&value, exp_case))
			error = true;
		else if (exp_case == v_exit_code
			&& !ft_get_exit_code_string(&name, &value, shell_data))
			error = true;
		else if (!ft_replace_name_with_value(string, token, name, value))
			error = true;
	}
	ft_free_name_and_value(&name, &value);
	return (!error);
}

static int	ft_get_expansion_case(char **string, bool in_double_quotes)
{
	char	next_char;

	next_char = *(*string + 1);
	if (ft_is_whitespace(next_char)
		|| (in_double_quotes && ft_is_char_quote(next_char)) || !next_char)
	{
		(*string)++;
		return (v_keep_dollar);
	}
	if (next_char == '$')
	{
		(*string) += 2;
		return (v_keep_dollar);
	}
	else if ((next_char) == '?')
		return (v_exit_code);
	else if (in_double_quotes)
		return (v_no_trim);
	else
		return (v_trim);
}

//at least remove the dollar
//otherwise replace the name with the value
static bool	ft_replace_name_with_value(char **string, char **token,
		char *variable_name, char *variable_value)
{
	int		variable_name_len;
	int		variable_value_len;
	int		total_len;
	char	*new_string;

	variable_name_len = 1;
	variable_value_len = 0;
	if (variable_name)
		variable_name_len += ft_strlen(variable_name);
	if (variable_value)
		variable_value_len = ft_strlen(variable_value);
	total_len = ft_strlen(*token) - variable_name_len + variable_value_len;
	new_string = malloc(sizeof(char) * (total_len + 1));
	if (!new_string)
		return (perror("error replacing variable name with value"), false);
	ft_strlcpy(new_string, *token, *string - *token + 1);
	if (variable_value)
		ft_strlcat(new_string, variable_value, total_len + 1);
	ft_strlcat(new_string, *string + variable_name_len, total_len + 1);
	free(*token);
	*token = new_string;
	*string = new_string;
	return (true);
}
