/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:59:19 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 17:50:07 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_check_for_syntax_error(t_tokens *token, t_tokens *next_token);
static bool	ft_is_operator(char token_type);
static void	ft_print_token_syntax_error(t_tokens *token);

//If there is a quote it searches for the next quote of the same type.
//If there is not a second quote of the same type this means the ammount of 
//quotes is not equal.
bool	ft_is_equal_quote_ammount(char *string)
{
	char	quote;

	quote = '\0';
	while (*string)
	{
		if ((*string == '\'' || *string == '\"'))
		{
			if (quote == '\0')
				quote = *string;
			else if (*string == quote)
				quote = '\0';
		}
		string++;
	}
	if (quote == '\'')
		ft_print_error_message("syntax error while looking for matching",
			"`", "'", "'");
	else if (quote == '"')
		ft_print_error_message("syntax error while looking for matching",
			"`", "\"", "'");
	return (quote == '\0');
}

bool	ft_is_syntax_error_in_tokens(t_list *tokens)
{
	t_tokens	*token;
	t_tokens	*next_token;

	token = (t_tokens *)tokens->content;
	if (token->type == pipe_operator)
	{
		ft_print_token_syntax_error(token);
		return (true);
	}
	while (tokens)
	{
		token = (t_tokens *)tokens->content;
		if (tokens->next)
			next_token = (t_tokens *)tokens->next->content;
		else
			next_token = NULL;
		if (ft_check_for_syntax_error(token, next_token))
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

//checks for operator no operator order
//only pipe && pipe at the end are considered an error
static bool	ft_check_for_syntax_error(t_tokens *token, t_tokens *next_token)
{
	if (token->type == syntax_error && *token->token == '|')
		return (ft_print_error_message("syntax error near unexpected token `",
				"|", "'", NULL), true);
	else if (token->type == syntax_error)
		return (ft_print_token_syntax_error(next_token), true);
	else if (ft_is_operator(token->type)
		&& (!next_token || ft_is_operator(next_token->type)))
	{
		if (token->type == pipe_operator && !next_token)
		{
			ft_print_token_syntax_error(token);
			return (true);
		}
		else if (token->type == pipe_operator && next_token)
			return (false);
		else
		{
			ft_print_token_syntax_error(next_token);
			return (true);
		}
	}
	return (false);
}

static bool	ft_is_operator(char token_type)
{
	if (token_type >= 1 && token_type <= 6)
		return (true);
	return (false);
}

static void	ft_print_token_syntax_error(t_tokens *token)
{
	if (token)
	{
		ft_print_error_message("syntax error near unexpected token `",
			token->token, "'", NULL);
	}
	else
	{
		ft_print_error_message("syntax error near unexpected token `newline'",
			NULL, NULL, NULL);
	}
}
