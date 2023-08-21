/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_to_char_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/04 18:52:13 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_process_token_list(t_list *tokens, char **arguments,
				int *i, bool copy);
static void	ft_copy_token_to_array(char **arguments, char **token, int *i);

bool	ft_token_list_to_args_array(char ***arguments, t_list *tokens)
{
	int			i;

	i = 0;
	ft_process_token_list(tokens, NULL, &i, false);
	*arguments = ft_calloc(i + 1, sizeof(char *));
	if (!*arguments)
		return (perror("error creatin one_sequence->args"), false);
	i = 0;
	ft_process_token_list(tokens, *arguments, &i, true);
	return (true);
}

static void	ft_process_token_list(t_list *tokens, char **arguments,
				int *i, bool copy)
{
	t_tokens	*one_token;

	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == text)
		{
			if (copy)
				ft_copy_token_to_array(arguments, &one_token->token, i);
			*i += 1;
		}
		tokens = tokens->next;
	}
}

static void	ft_copy_token_to_array(char **arguments, char **token, int *i)
{
	arguments[*i] = *token;
	*token = NULL;
}
