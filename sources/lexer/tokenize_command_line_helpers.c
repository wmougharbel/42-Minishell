/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_command_line_helpers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:41:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 18:21:22 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_to_next_non_delimiter(char **command_line)
{
	while (ft_is_whitespace(**command_line))
		*command_line += 1;
}

bool	ft_is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

void	ft_skip_quote_block(char **string, bool	only_single_quotes,
			bool end_with_quote)
{
	char	quote;

	while (**string == '\'' || (!only_single_quotes && **string == '\"'))
	{
		quote = '\'';
		if (**string == '\"' && !only_single_quotes)
			quote = '\"';
		while (++(*string) && **string != quote)
			;
		if (**string && **string == quote && !end_with_quote)
			*string += 1;
	}
}

void	ft_move_while_same_char(char **command_line, char c)
{
	int	max_len;

	if (c == '<' || c == '>')
		max_len = 2;
	else
		max_len = -1;
	while ((max_len == -1 || max_len-- > 0) && **command_line == c)
		*command_line += 1;
}
