/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:08:25 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 00:55:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_shell_data(t_shell_data *shell_data, bool everything)
{
	ft_free_ptr_and_set_to_null((void **)&shell_data->cmd_line);
	ft_free_ptr_and_set_to_null((void **)&shell_data->process_ids);
	ft_free_double_pointer_char(&shell_data->heredocs);
	ft_free_double_pointer_char(&shell_data->envp_array);
	if (shell_data->cmd_sequences)
		ft_lstclear(&shell_data->cmd_sequences, ft_clear_command_sequence);
	else
		ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	shell_data->cmd_sequences = NULL;
	shell_data->all_tokens = NULL;
	if (everything)
	{
		ft_lstclear(&shell_data->env_list, ft_clear_env_variable);
		free(shell_data);
	}
}

void	ft_clear_command_sequence(void *node)
{
	t_cmd_sequences	*sequence;

	if (!node)
		return ;
	sequence = (t_cmd_sequences *)node;
	ft_free_ptr_and_set_to_null((void **)&sequence->command_path);
	ft_free_double_pointer_char(&sequence->envp_command_paths);
	if (sequence->args)
		ft_free_double_pointer_char(&sequence->args);
	ft_lstclear(&sequence->tokens, ft_clear_token);
	free(node);
}

void	ft_clear_token(void *node)
{
	t_tokens	*token;

	if (!node)
		return ;
	token = (t_tokens *)node;
	if (token->token)
		free(token->token);
	free(node);
}

void	ft_clear_env_variable(void *node)
{
	t_env	*env_variable;

	if (!node)
		return ;
	env_variable = (t_env *)node;
	ft_free_ptr_and_set_to_null((void **)&env_variable->name);
	ft_free_ptr_and_set_to_null((void **)&env_variable->value);
	free(node);
}
