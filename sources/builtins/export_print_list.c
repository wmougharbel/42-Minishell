/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:35:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 20:16:52 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		*ft_duplicate_env_variable(void *env_variable);
static t_list	*ft_sort_list_asci(t_list *lst);
static void		ft_swap(void **var1, void **var2);

int	print_export(t_list **env_list)
{
	t_list	*sorted_env_list;
	t_list	*start_of_sorted_list;
	t_env	*one_env_variable;

	sorted_env_list = ft_lstmap(*env_list,
			ft_duplicate_env_variable, ft_clear_env_variable);
	if (!sorted_env_list && *env_list)
		return (__system_call_error);
	sorted_env_list = ft_sort_list_asci(sorted_env_list);
	start_of_sorted_list = sorted_env_list;
	while (sorted_env_list)
	{
		one_env_variable = (t_env *)sorted_env_list->content;
		printf("declare -x %s", one_env_variable->name);
		if (one_env_variable->value)
			printf("=\"%s\"\n", one_env_variable->value);
		else if (one_env_variable->print_empty_quotes)
			printf("=\"\"\n");
		else
			printf("\n");
		sorted_env_list = sorted_env_list->next;
	}
	ft_lstclear(&start_of_sorted_list, ft_clear_env_variable);
	return (__success);
}

static void	*ft_duplicate_env_variable(void *env_variable)
{
	t_env	*one_env_variable;
	t_env	*new_env_variable;

	one_env_variable = (t_env *)env_variable;
	new_env_variable = ft_calloc(1, sizeof(t_env));
	if (!new_env_variable)
		return (NULL);
	new_env_variable->name = ft_strdup(one_env_variable->name);
	if (one_env_variable->value)
		new_env_variable->value = ft_strdup(one_env_variable->value);
	else
		new_env_variable->value = NULL;
	new_env_variable->print_empty_quotes = one_env_variable->print_empty_quotes;
	if (!new_env_variable->name
		|| (one_env_variable->value && !new_env_variable->value))
		return (ft_clear_env_variable((void *)new_env_variable), NULL);
	return ((void *)new_env_variable);
}

static t_list	*ft_sort_list_asci(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (lst->next)
	{
		if (ft_strcmp(((t_env *)lst->content)->name,
				((t_env *)lst->next->content)->name) > 0)
		{
			ft_swap(&lst->content, &lst->next->content);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

static void	ft_swap(void **var1, void **var2)
{
	void	*swap;

	swap = *var1;
	*var1 = *var2;
	*var2 = swap;
}
