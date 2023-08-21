/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 20:38:40 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_lstremove(t_list **env_list_new, t_list *env_variable_to_remove);

int	ft_unset(char **arguments, t_list **env_list_new, t_shell_data *shell_data)
{
	t_list	*env_variable_to_remove;
	bool	syntax_error;
	int		i;

	i = 1;
	syntax_error = false;
	if (!*env_list_new)
		return (__success);
	while (arguments[i])
	{
		if (ft_is_syntax_error_in_env_name(arguments[i]))
			syntax_error = true;
		env_variable_to_remove = ft_find_env_variable(arguments[i],
				*env_list_new);
		if (env_variable_to_remove && !ft_strcmp(arguments[i], "PWD"))
			shell_data->print_quotes_for_oldpwd = true;
		if (env_variable_to_remove)
			ft_lstremove(env_list_new, env_variable_to_remove);
		i++;
	}
	if (syntax_error)
		return (__syntax_error);
	return (__success);
}

static void	ft_lstremove(t_list **env_list_new, t_list *env_variable_to_remove)
{
	t_list	*prev;

	if (!env_variable_to_remove)
		return ;
	prev = *env_list_new;
	if (env_variable_to_remove == *env_list_new)
		*env_list_new = env_variable_to_remove->next;
	else
	{
		while (prev->next != env_variable_to_remove)
			prev = prev->next;
		prev->next = env_variable_to_remove->next;
	}
	ft_lstdelone(env_variable_to_remove, ft_clear_env_variable);
}
