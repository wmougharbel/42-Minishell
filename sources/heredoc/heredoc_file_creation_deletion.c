/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_creation_deletion.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:41:28 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 19:26:44 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_heredocs(t_list *tokens);
static char	*ft_create_here_doc_name(int i);

bool	ft_create_heredoc_files(t_shell_data *shell_data)
{
	int	number_of_heredocs;
	int	i;

	i = 0;
	number_of_heredocs = ft_count_heredocs(shell_data->all_tokens);
	if (number_of_heredocs == 0)
		return (true);
	shell_data->heredocs = ft_calloc(number_of_heredocs + 1, sizeof(char *));
	if (!shell_data->heredocs)
		return (perror("error creating shell_data->heredocs"), false);
	while (i < number_of_heredocs)
	{
		shell_data->heredocs[i] = ft_create_here_doc_name(i);
		if (!shell_data->heredocs[i])
			return (false);
		i++;
	}
	return (true);
}

static int	ft_count_heredocs(t_list *tokens)
{
	t_tokens	*one_token;
	int			i;

	i = 0;
	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == redirection_in_heredoc)
			one_token->heredoc_number = i++;
		tokens = tokens->next;
	}
	return (i);
}

static char	*ft_create_here_doc_name(int i)
{
	char	*file_number;
	char	*heredoc_filename;

	heredoc_filename = NULL;
	file_number = ft_itoa(i);
	if (!file_number)
		return (perror("error creating the file_number string"), NULL);
	heredoc_filename = ft_strjoin("heredocs/.heredoc_", file_number);
	free(file_number);
	if (!heredoc_filename)
		return (perror("error creating the herdoc_filename"), NULL);
	return (heredoc_filename);
}

void	ft_delete_heredoc_files(char **heredoc_files)
{
	int	i;

	i = 0;
	if (!heredoc_files)
		return ;
	while (heredoc_files[i])
	{
		if (unlink(heredoc_files[i]) == -1)
			;
		i++;
	}
}
