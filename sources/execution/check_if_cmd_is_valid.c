/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_cmd_is_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:20:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 18:01:11 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_cmd_valid(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	char	*command;

	command = sequence_to_execute->args[0];
	if (!command)
		return (false);
	if (ft_strchr(command, '/') || !ft_find_env_variable("PATH",
			shell_data->env_list))
	{
		if (!ft_check_file(command, shell_data))
			return (false);
		sequence_to_execute->command_path = ft_strdup(command);
		if (!sequence_to_execute->command_path)
			return (perror("error duplicating command"), false);
		return (true);
	}
	if (*command && !ft_search_in_env_paths_for_cmd(shell_data,
			sequence_to_execute))
		return (false);
	if (sequence_to_execute->command_path)
		return (true);
	ft_print_error_message(command, ": command not found", NULL, NULL);
	shell_data->exit_code = 127;
	return (false);
}

bool	ft_is_file_existent(char *command, t_shell_data *shell_data)
{
	if (access(command, F_OK))
	{
		shell_data->exit_code = 127;
		ft_print_error_message(command, ": No such file or directory", NULL,
			NULL);
		return (false);
	}
	return (true);
}

bool	ft_is_directory(char *command, t_shell_data *shell_data)
{
	struct stat	file_info;

	ft_memset(&file_info, 0, sizeof(file_info));
	if (stat(command, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			shell_data->exit_code = 126;
			ft_print_error_message(command, ": is a directory", NULL, NULL);
			return (true);
		}
	}
	else
		return (perror("stat"), true);
	return (false);
}

bool	ft_is_executable(char *command, t_shell_data *shell_data)
{
	if (access(command, X_OK) == 0)
		return (true);
	else
	{
		shell_data->exit_code = 126;
		ft_print_error_message(command, ": Permission denied", NULL, NULL);
		return (false);
	}
}

bool	ft_search_in_env_paths_for_cmd(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	if (!ft_get_envp_paths(shell_data->envp_array,
			&sequence_to_execute->envp_command_paths))
		return (false);
	if (!ft_get_cmd_path(sequence_to_execute->envp_command_paths,
			sequence_to_execute->args[0], &sequence_to_execute->command_path))
		return (false);
	return (true);
}
