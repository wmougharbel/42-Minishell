/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:07:55 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 20:51:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_read_heredocs_in_child_process(t_shell_data *shell_data);
static void	ft_process_heredoc_reading(t_shell_data *shell_data);
static int	ft_open_reading_for_heredocs(t_list *tokens,
				char **heredocs, t_shell_data *shell_data);
static bool	ft_fill_heredoc(char *heredoc_name, char **delimiter,
				t_shell_data *shell_data);

int	ft_handle_heredocs(t_shell_data *shell_data)
{
	int	status;

	status = __success;
	if (!ft_create_heredoc_files(shell_data))
		return (__system_call_error);
	if (shell_data->heredocs)
		status = ft_read_heredocs_in_child_process(shell_data);
	if (status != __success)
		shell_data->exit_code = 1;
	return (status);
}

static int	ft_read_heredocs_in_child_process(t_shell_data *shell_data)
{
	pid_t	process_id;
	int		stat_loc;
	int		exit_code;

	stat_loc = 0;
	exit_code = 0;
	process_id = fork();
	if (process_id == -1)
		return (perror("error fork for heredoc"), false);
	if (process_id == 0)
		ft_process_heredoc_reading(shell_data);
	signal(SIGINT, ft_handle_sigint_in_parent_during_execution);
	waitpid(process_id, &stat_loc, 0);
	ft_get_exit_code(&exit_code, stat_loc, true, false);
	ft_set_minisell_signals();
	if (exit_code == 1)
		return (__system_call_error);
	else if (exit_code > 1)
		return (__stop_execution);
	return (__success);
}

static void	ft_process_heredoc_reading(t_shell_data *shell_data)
{
	int	exit_code;

	shell_data->add_no_quotes = true;
	exit_code = ft_open_reading_for_heredocs(shell_data->all_tokens,
			shell_data->heredocs, shell_data);
	ft_free_shell_data(shell_data, true);
	exit(exit_code);
}

static int	ft_open_reading_for_heredocs(t_list *tokens,
			char **heredocs, t_shell_data *shell_data)
{
	t_tokens	*one_token;
	t_tokens	*next_token;
	int			i;

	signal(SIGINT, SIG_DFL);
	i = 0;
	while (tokens->next)
	{
		one_token = (t_tokens *)tokens->content;
		next_token = (t_tokens *)tokens->next->content;
		if (one_token->type == redirection_in_heredoc)
		{
			if (!ft_fill_heredoc(heredocs[i], &next_token->token, shell_data))
				return (1);
			i++;
		}
		tokens = tokens->next;
	}
	return (0);
}

static bool	ft_fill_heredoc(char *heredoc_name, char **delimiter,
			t_shell_data *shell_data)
{
	char	*line;
	int		heredoc_fd;
	bool	no_expansion;

	no_expansion = ft_is_quotes_in_delimiter(*delimiter);
	heredoc_fd = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC, RW_R__R__);
	if (heredoc_fd == -1)
		return (perror("error opening heredoc"), false);
	if (no_expansion && !ft_remove_quotes_from_string(delimiter))
		return (close(heredoc_fd), false);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, *delimiter))
			break ;
		if (!no_expansion
			&& !ft_expand_variables_in_string(&line, shell_data, true))
			return (free(line), close(heredoc_fd), false);
		ft_putendl_fd(line, heredoc_fd);
		free(line);
	}
	ft_free_ptr_and_set_to_null((void **)&line);
	close(heredoc_fd);
	return (true);
}
