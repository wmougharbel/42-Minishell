/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_command_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:48:01 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 18:50:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_find_next_token(char **string, char **start, t_list **tokens);
static bool	ft_create_one_token(char *start, char *end, t_list **tokens);

int	ft_tokenize_command_line(char *cmd_line, t_list **tokens)
{
	char				*start;

	while (*cmd_line)
	{
		ft_skip_to_next_non_delimiter(&cmd_line);
		start = cmd_line;
		ft_find_next_token(&cmd_line, &start, tokens);
		if (start != cmd_line
			&& !ft_create_one_token(start, cmd_line, tokens))
		{
			return (__system_call_error);
		}
	}
	if (!*tokens)
		return (__no_history);
	return (__success);
}

//seaparates the string by whitespace and opeartors
static int	ft_find_next_token(char **string, char **start, t_list **tokens)
{
	while (**string)
	{
		ft_skip_quote_block(string, false, false);
		if (**string == '<' || **string == '>' || **string == '|')
		{
			if (*start != *string)
			{
				if (!ft_create_one_token(*start, *string, tokens))
					return (__system_call_error);
				*start = *string;
			}
			ft_move_while_same_char(string, **string);
			break ;
		}
		if (**string == ' ' || **string == '\t')
			break ;
		if (**string)
			*string += 1;
	}
	return (__success);
}

static bool	ft_create_one_token(char *start, char *end, t_list **tokens)
{
	t_tokens	*token;
	t_list		*new_node;
	int			len;
	char		*string;

	token = ft_calloc(1, sizeof(t_tokens));
	if (!token)
		return (false);
	new_node = ft_lstnew((void *)token);
	if (!new_node)
		return (free(token), false);
	ft_lstadd_back(tokens, new_node);
	len = end - start;
	string = ft_substr(start, 0, len);
	if (!string)
	{
		ft_lstclear(tokens, ft_clear_token);
		return (perror("error creating string for token"), false);
	}
	token->token = string;
	return (true);
}
