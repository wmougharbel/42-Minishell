/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_sequences.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:59:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 01:29:33 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_find_pipe_operator(t_list **tokens);
static bool	ft_assign_tokens(t_list *start_of_tokens, t_list **cmd_sequences);

int	ft_split_tokens_in_sequences(t_list *tokens, t_list **cmd_sequences)
{
	t_list	*start_of_tokens;
	bool	pipe_inside;

	start_of_tokens = tokens;
	pipe_inside = true;
	if (!tokens)
		return (__stop_execution);
	while (tokens)
	{
		if (pipe_inside)
			pipe_inside = ft_find_pipe_operator(&tokens);
		if (pipe_inside || !tokens)
		{
			if (!ft_assign_tokens(start_of_tokens, cmd_sequences))
			{
				if (cmd_sequences)
					ft_lstclear(&start_of_tokens, ft_clear_token);
				return (__system_call_error);
			}
			start_of_tokens = tokens;
		}
		else if (tokens)
			tokens = tokens->next;
	}
	return (__success);
}

static bool	ft_find_pipe_operator(t_list **tokens)
{
	t_list		*previous;
	t_list		*next;
	t_tokens	*token;

	previous = NULL;
	next = NULL;
	while (*tokens)
	{
		next = (*tokens)->next;
		token = (t_tokens *)((*tokens)->content);
		if (token->type == pipe_operator)
		{
			ft_cut_out_node(tokens, previous, *tokens, NULL);
			*tokens = next;
			return (true);
		}
		else
			previous = *tokens;
		*tokens = next;
	}
	return (false);
}

static bool	ft_assign_tokens(t_list *start_of_tokens, t_list **cmd_sequences)
{
	t_list				*new_sequence_node;
	t_cmd_sequences		*one_sequence;

	one_sequence = ft_calloc(1, sizeof(t_cmd_sequences));
	if (!one_sequence)
		return (perror("error creating one_sequence"), false);
	new_sequence_node = ft_lstnew((void *)one_sequence);
	if (!new_sequence_node)
	{
		free(one_sequence);
		perror("error creating new_sequence_node");
		return (false);
	}
	one_sequence->tokens = start_of_tokens;
	ft_lstadd_back(cmd_sequences, new_sequence_node);
	return (true);
}
