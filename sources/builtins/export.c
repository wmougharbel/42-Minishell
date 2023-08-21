/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:56:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 00:15:51 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **arguemnts, t_list **env_list)
{
	int		i;
	int		status;
	bool	syntax_error;

	i = 0;
	syntax_error = false;
	while (arguemnts[++i])
	{
		if (!ft_strcmp(arguemnts[i], "_"))
			continue ;
		status = ft_update_or_add_env_variable(arguemnts[i],
				env_list, NULL, NULL);
		if (status == __syntax_error)
			syntax_error = true;
		else if (status)
			return (status);
	}
	if (i == 1)
	{
		if (print_export(env_list) == __system_call_error)
			return (__system_call_error);
	}
	if (syntax_error)
		return (__syntax_error);
	return (__success);
}

//only allocated memory for name && value
int	ft_update_or_add_env_variable(char *argument, t_list **env_list,
		char *name, char *value)
{
	t_list	*env_update;
	bool	print_empty_quotes;

	print_empty_quotes = false;
	if (!name && !value)
	{
		if (ft_is_syntax_error_in_env_name(argument))
			return (__syntax_error);
		if (!ft_create_name_and_value(argument, &name,
				&value, &print_empty_quotes))
			return (__system_call_error);
	}
	else if (name && value)
		print_empty_quotes = true;
	env_update = ft_find_env_variable(name, *env_list);
	if (env_update)
		ft_assign((t_env *)env_update->content,
			name, value, print_empty_quotes);
	else if (!store_var_in_node(env_list, name, value, print_empty_quotes))
		return (ft_free_name_and_value(&name, &value), __system_call_error);
	return (__success);
}

bool	ft_is_syntax_error_in_env_name(char *string)
{
	bool	syntax_error;
	int		i;

	syntax_error = false;
	i = 0;
	if (!(ft_isalpha(string[i]) || string[i++] == '_'))
		syntax_error = true;
	else
	{
		while (!syntax_error && string[i] && string[i] != '=')
		{
			if (!(ft_isalnum(string[i]) || string[i] == '_'))
				syntax_error = true;
			i++;
		}
	}
	if (syntax_error)
	{
		ft_print_error_message("export: `", string,
			"': not a valid identifier", NULL);
		return (true);
	}
	return (false);
}

bool	store_var_in_node(t_list **env_list, char *name,
	char *value, bool print_empty_quotes)
{
	t_list	*new_node;
	t_env	*env_variable;

	env_variable = ft_calloc(1, sizeof(t_env));
	if (!env_variable)
		return (perror("error creating env_variable"), false);
	new_node = ft_lstnew((void *)env_variable);
	if (!new_node)
		return (free(env_variable),
			perror("error creating new_node for env_variable"), false);
	ft_assign(env_variable, name, value, print_empty_quotes);
	ft_lstadd_front(env_list, new_node);
	return (true);
}

void	ft_assign(t_env *env_variable,
	char *name, char *value, bool print_empty_quotes)
{
	if (name)
	{
		ft_free_ptr_and_set_to_null((void **)&env_variable->name);
		env_variable->name = name;
	}
	ft_free_ptr_and_set_to_null((void **)&env_variable->value);
	env_variable->value = value;
	if (!env_variable->value && print_empty_quotes)
		env_variable->print_empty_quotes = true;
	else
		env_variable->print_empty_quotes = false;
}
