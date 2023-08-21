/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 19:07:00 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_command_in_child(t_shell_data *shell_data,
	int number_of_commands, t_cmd_sequences *sequence_to_execute,
	int command_index)
{
	int	exit_code;

	ft_restore_default_signals();
	shell_data->exit_code = 1;
	shell_data->in_child_process = true;
	if (ft_handle_redirection_operators(sequence_to_execute,
			sequence_to_execute->tokens, shell_data->heredocs))
		;
	else if (!ft_token_list_to_args_array(&sequence_to_execute->args,
			sequence_to_execute->tokens))
		;
	else if (!ft_env_list_to_envp_array(shell_data))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute,
			number_of_commands, command_index))
		;
	else if (ft_execution_of_command(shell_data, sequence_to_execute, false))
		;
	exit_code = shell_data->exit_code;
	rl_clear_history();
	ft_close_all_pipes(shell_data->pipe_fds, number_of_commands - 1);
	ft_free_double_pointer_int(&shell_data->pipe_fds, number_of_commands - 1);
	ft_free_shell_data(shell_data, true);
	exit(exit_code);
}

int	ft_execution_of_command(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, bool single_builtin)
{
	int	status;

	status = ft_execute_builtin_if_builtin(shell_data, sequence_to_execute);
	if (single_builtin)
		return (status);
	else if (!single_builtin && status != __no_builtin_found)
		return (status);
	else if (!ft_is_cmd_valid(shell_data, sequence_to_execute))
		;
	else if (execve(sequence_to_execute->command_path,
			sequence_to_execute->args, shell_data->envp_array) == -1)
		perror("minishell: execve");
	return (__mini_error);
}

int	ft_execute_builtin_if_builtin(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	char	*command;
	int		status;

	status = __success;
	command = sequence_to_execute->args[0];
	status = get_builtin_command(shell_data, sequence_to_execute, command,
			status);
	if (status == __success || status == __success_but_stop)
		shell_data->exit_code = 0;
	return (status);
}

int	get_builtin_command(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, char *command, int status)
{
	if (!ft_strcmp("echo", command))
		ft_echo(sequence_to_execute->args);
	else if (!ft_strcmp("cd", command))
		status = ft_cd(sequence_to_execute->args, shell_data->env_list,
				&shell_data->print_quotes_for_oldpwd);
	else if (!ft_strcmp("pwd", command))
		status = ft_pwd(NULL, true);
	else if (!ft_strcmp("export", command))
		status = ft_export(sequence_to_execute->args, &shell_data->env_list);
	else if (!ft_strcmp("unset", command))
		status = ft_unset(sequence_to_execute->args, &shell_data->env_list,
				shell_data);
	else if (!ft_strcmp("env", command))
		ft_print_env_list(shell_data->env_list);
	else if (!ft_strcmp("exit", command))
		status = ft_exit(sequence_to_execute->args, shell_data);
	else
		return (__no_builtin_found);
	return (status);
}
