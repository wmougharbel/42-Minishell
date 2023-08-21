/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/05 01:30:15 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_do_redirection(t_cmd_sequences *sequence,
				t_tokens *operator_node, t_tokens *file_node, char **heredocs);
static bool	ft_input_redirection(int *input_fd, t_tokens *operator_node,
				t_tokens *file_node, char **heredocs);
static bool	ft_output_redirection(int *output_fd, char operator,
				t_tokens *file_node);

int	ft_handle_redirection_operators(t_cmd_sequences *sequence,
	t_list *tokens, char **heredocs)
{
	t_tokens	*current;
	t_tokens	*next;

	sequence->output_fd = 1;
	while (tokens->next)
	{
		current = (t_tokens *)tokens->content;
		next = (t_tokens *)tokens->next->content;
		if (current->type >= redirection_in
			&& current->type <= redirection_out_append)
		{
			if (!ft_do_redirection(sequence, current, next, heredocs))
				return (__stop_execution);
			tokens = tokens->next->next;
		}
		else
			tokens = tokens->next;
		if (!tokens)
			break ;
	}
	return (__success);
}

static bool	ft_do_redirection(t_cmd_sequences *sequence,
		t_tokens *operator_node, t_tokens *file_node, char **heredocs)
{
	bool	status;

	status = true;
	if (operator_node->type == redirection_in
		|| operator_node->type == redirection_in_heredoc)
	{
		status = ft_input_redirection(&sequence->input_fd,
				operator_node, file_node, heredocs);
	}
	else if (operator_node->type == redirection_out_trunc
		|| operator_node->type == redirection_out_append)
	{
		status = ft_output_redirection(&sequence->output_fd,
				operator_node->type, file_node);
	}
	if (!status)
	{
		if (sequence->input_fd > 0)
			close(sequence->input_fd);
		if (sequence->output_fd > 1)
			close(sequence->output_fd);
	}
	return (status);
}

static bool	ft_output_redirection(int *output_fd, char operator,
				t_tokens *file_node)
{
	int		fd;

	fd = 1;
	if (operator == redirection_out_trunc)
		fd = open(file_node->token, O_WRONLY | O_TRUNC | O_CREAT, RW_R__R__);
	else if (operator == redirection_out_append)
		fd = open(file_node->token, O_WRONLY | O_APPEND | O_CREAT, RW_R__R__);
	if (*output_fd > 1)
		close(*output_fd);
	file_node->type = redirection_filename;
	*output_fd = fd;
	if (fd == -1)
		return (ft_print_error_message(file_node->token, ": ",
				strerror(errno), NULL), false);
	return (true);
}

static bool	ft_input_redirection(int *input_fd, t_tokens *operator_node,
		t_tokens *file_node, char **heredocs)
{
	int	fd;

	fd = 0;
	if (operator_node->type == redirection_in)
		fd = open(file_node->token, O_RDONLY);
	else if (operator_node->type == redirection_in_heredoc)
		fd = open(heredocs[operator_node->heredoc_number], O_RDONLY);
	if (*input_fd > 0)
		close(*input_fd);
	file_node->type = redirection_filename;
	*input_fd = fd;
	if (fd == -1)
		return (ft_print_error_message(file_node->token, ": ",
				strerror(errno), NULL), false);
	return (true);
}
