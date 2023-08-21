/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:16:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 21:11:07 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_commands(t_shell_data *shell_data)
{
	int		number_of_commands;
	int		status;

	status = __success;
	number_of_commands = ft_lstsize(shell_data->cmd_sequences);
	if (!ft_create_pipes(shell_data, number_of_commands - 1))
		return (__system_call_error);
	if (number_of_commands == 1 && ft_is_builtin((t_cmd_sequences *)
			shell_data->cmd_sequences->content))
	{
		status = ft_execute_single_builtin(shell_data, number_of_commands,
				(t_cmd_sequences *)shell_data->cmd_sequences->content, 0);
		ft_set_minisell_signals();
		return (status);
	}
	if (!ft_fork_child_processes(shell_data, number_of_commands))
		status = __system_call_error;
	if (status == __success)
		ft_set_singals_in_parent_during_execution();
	ft_close_all_pipes(shell_data->pipe_fds, number_of_commands - 1);
	ft_free_double_pointer_int(&shell_data->pipe_fds, number_of_commands - 1);
	ft_wait_for_childs_and_get_exit_code(shell_data, number_of_commands);
	ft_set_minisell_signals();
	return (status);
}

bool	ft_create_pipes(t_shell_data *shell_data, int number_of_pipes)
{
	int	i;

	if (number_of_pipes == 0)
		return (true);
	shell_data->pipe_fds = ft_calloc(number_of_pipes, sizeof(int *));
	if (!shell_data->pipe_fds)
		return (perror("error creating shell_data->pipe_fds"), false);
	i = 0;
	while (i < number_of_pipes)
	{
		shell_data->pipe_fds[i] = ft_calloc(2, sizeof(int));
		if (!shell_data->pipe_fds[i] || pipe(shell_data->pipe_fds[i]) == -1)
		{
			ft_close_all_pipes(shell_data->pipe_fds, i);
			ft_free_double_pointer_int(&shell_data->pipe_fds, i);
			if (!shell_data->pipe_fds[i])
				return (perror("error creating shell_data->pipe_fds[]"), false);
			else
				return (perror("error creating pipe"), false);
		}
		i++;
	}
	return (true);
}

bool	ft_fork_child_processes(t_shell_data *shell_data,
	int number_of_commands)
{
	int		i;
	t_list	*cmd_sequences;

	cmd_sequences = shell_data->cmd_sequences;
	shell_data->process_ids = ft_calloc(number_of_commands, sizeof(pid_t));
	if (!shell_data->process_ids)
		return (perror("error creating shell_data->process_ids"), false);
	i = 0;
	while (i < number_of_commands)
	{
		shell_data->process_ids[i] = fork();
		if (shell_data->process_ids[i] == -1)
			return (perror("error forking child process"), false);
		if (shell_data->process_ids[i] == 0)
			ft_execute_command_in_child(shell_data, number_of_commands,
				(t_cmd_sequences *)cmd_sequences->content, i);
		i++;
		cmd_sequences = cmd_sequences->next;
	}
	return (true);
}

void	ft_wait_for_childs_and_get_exit_code(t_shell_data *shell_data,
	int number_of_commands)
{
	int		stat_loc;
	int		exit_code;
	int		i;
	bool	first_encounter;

	exit_code = 0;
	i = number_of_commands;
	first_encounter = true;
	while (i > 0)
	{
		i--;
		if (shell_data->process_ids[i] > 0)
		{
			waitpid(shell_data->process_ids[i], &stat_loc, 0);
			ft_get_exit_code(&exit_code, stat_loc, first_encounter, true);
			first_encounter = false;
		}
	}
	shell_data->exit_code = exit_code;
}

void	ft_get_exit_code(int *exit_code, int stat_loc, bool first_encounter,
	bool reset_signal_number)
{
	if (reset_signal_number)
		g_signal_number = 0;
	if (WIFEXITED(stat_loc))
	{
		if (first_encounter && WEXITSTATUS(stat_loc))
			*exit_code = WEXITSTATUS(stat_loc);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		if (first_encounter)
			*exit_code = WTERMSIG(stat_loc) + 128;
	}
}
