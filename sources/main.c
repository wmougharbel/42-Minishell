/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:48:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 20:38:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//what to do when we get arguments for the minishell? -> nothing
int	main(int argc, char **argv, char **envp)
{
	t_shell_data	*shell_data;
	int				status;

	(void)argc;
	(void)argv;
	ft_prepare_minishell(&shell_data, envp);
	while (1)
	{
		shell_data->cmd_line = readline(PROMPT);
		if (shell_data->cmd_line && *shell_data->cmd_line)
		{
			status = ft_process_command_line(shell_data);
			if (status == __general_syntax_error)
				shell_data->exit_code = 2;
			if (status == __system_call_error)
				return (ft_free_shell_data(shell_data, true), exit(1), 1);
			if (status != __no_history)
				add_history(shell_data->cmd_line);
		}
		else if (!shell_data->cmd_line)
			ft_exit_ctrl_d(shell_data);
		ft_delete_heredoc_files(shell_data->heredocs);
		ft_free_shell_data(shell_data, false);
	}
	exit (0);
}

int	ft_process_command_line(t_shell_data *shell_data)
{
	int	status;

	if (!ft_is_equal_quote_ammount(shell_data->cmd_line))
		return (__general_syntax_error);
	status = ft_tokenize_command_line(shell_data->cmd_line,
			&shell_data->all_tokens);
	if (status)
		return (status);
	ft_lstiter(shell_data->all_tokens, ft_assign_token_type);
	if (ft_is_syntax_error_in_tokens(shell_data->all_tokens))
		return (__general_syntax_error);
	status = ft_handle_heredocs(shell_data);
	if (status)
		return (status);
	if (!ft_expand_variables_in_tokens(&shell_data->all_tokens, shell_data))
		return (__system_call_error);
	if (!ft_remove_quotes_from_tokens(shell_data->all_tokens))
		return (__system_call_error);
	status = ft_split_tokens_in_sequences(shell_data->all_tokens,
			&shell_data->cmd_sequences);
	if (status)
		return (status);
	status = ft_execute_commands(shell_data);
	return (status);
}

void	ft_exit_ctrl_d(t_shell_data *shell_data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	ft_free_shell_data(shell_data, true);
	exit(0);
}
