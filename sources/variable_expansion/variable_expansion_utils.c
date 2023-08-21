/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:05:12 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 15:50:17 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cut_out_node(t_list **tokens, t_list *previous,
			t_list *current, t_list *next)
{
	t_list	*temp;

	temp = current;
	if (previous)
		previous->next = next;
	if (temp == *tokens)
		*tokens = current->next;
	ft_lstdelone(temp, ft_clear_token);
}

void	ft_update_quote_state(bool *in_single_quotes,
				bool *in_double_quotes, char c)
{
	if (c == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	else if (c == '\"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

void	ft_skip_whitespace(char *string, int *i)
{
	while (string[*i] && (ft_is_whitespace(string[*i])
			|| string[*i] == '\n'))
		*i += 1;
}

bool	ft_is_char_quote(char c)
{
	return (c == '\'' || c == '\"');
}
