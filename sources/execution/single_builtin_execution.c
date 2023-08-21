/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:50:13 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 02:17:04 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_save_standard_fds(t_shell_data *shell_data);
static bool	ft_restore_standard_fds(t_shell_data *shell_data);

int	ft_execute_single_builtin(t_shell_data *shell_data, int number_of_commands,
		t_cmd_sequences *sequence_to_execute, int command_index)
{
	int	status;

	status = __success;
	shell_data->exit_code = 1;
	if (!ft_save_standard_fds(shell_data))
		return (__system_call_error);
	ft_restore_default_signals();
	status = ft_handle_redirection_operators(sequence_to_execute,
			sequence_to_execute->tokens, shell_data->heredocs);
	if (!status && !ft_token_list_to_args_array(&sequence_to_execute->args,
			sequence_to_execute->tokens))
		status = __system_call_error;
	if (!status && !ft_duplication_of_fds(shell_data->pipe_fds,
			sequence_to_execute, number_of_commands, command_index))
		status = __system_call_error;
	if (!status)
		status = ft_execution_of_command(shell_data, sequence_to_execute, true);
	if (status != __system_call_error && !ft_restore_standard_fds(shell_data))
		status = __system_call_error;
	return (status);
}

bool	ft_is_builtin(t_cmd_sequences *sequence_to_execute)
{
	t_tokens	*token;
	char		*command;

	token = (t_tokens *)sequence_to_execute->tokens->content;
	command = token->token;
	if (!ft_strcmp("echo", command))
		return (true);
	else if (!ft_strcmp("cd", command))
		return (true);
	else if (!ft_strcmp("pwd", command))
		return (true);
	else if (!ft_strcmp("export", command))
		return (true);
	else if (!ft_strcmp("unset", command))
		return (true);
	else if (!ft_strcmp("env", command))
		return (true);
	else if (!ft_strcmp("exit", command))
		return (true);
	else
		return (false);
}

static bool	ft_save_standard_fds(t_shell_data *shell_data)
{
	shell_data->default_stdin = dup(STDIN_FILENO);
	if (shell_data->default_stdin == -1)
		return (perror("error saving default stdin"), false);
	shell_data->default_stdout = dup(STDOUT_FILENO);
	if (shell_data->default_stdout == -1)
	{
		close(shell_data->default_stdin);
		return (perror("error saving default stdout"), false);
	}
	return (true);
}

static bool	ft_restore_standard_fds(t_shell_data *shell_data)
{
	bool	status;

	status = true;
	if (dup2(shell_data->default_stdin, STDIN_FILENO) == -1)
	{
		perror("error restoring default stdin");
		status = false;
	}
	else if (dup2(shell_data->default_stdout, STDOUT_FILENO) == -1)
	{
		perror("error restoring default stdout");
		status = false;
	}
	return (status);
}
