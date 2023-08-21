/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:38:02 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 22:22:31 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_process_quote_string(char *string, char *new_string,
				void (*copy_or_count)(char *, int *, char), int *count);

bool	ft_remove_quotes_from_tokens(t_list *tokens)
{
	t_tokens	*one_token;

	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == text)
		{
			if (!ft_remove_quotes_from_string(&one_token->token))
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

//pass string as reference
bool	ft_remove_quotes_from_string(char **string)
{
	char	*new_string;
	int		len;

	len = 0;
	if (!*string)
		return (true);
	ft_process_quote_string(*string, NULL, ft_count_length, &len);
	if (len == (int)ft_strlen(*string))
		return (true);
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (perror("malloc - remove quotes from elements"), false);
	new_string[len] = '\0';
	ft_process_quote_string(*string, new_string, ft_copy_char, NULL);
	free(*string);
	*string = new_string;
	return (true);
}

static void	ft_process_quote_string(char *string, char *new_string,
		void (*copy_or_count)(char *, int *, char), int *count)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '\"'))
		{
			quote = string[i];
			while (string[++i] && string[i] != quote)
				copy_or_count(new_string + j++, count, string[i]);
			if (string[i])
				i++;
		}
		else
			copy_or_count(new_string + j++, count, string[i++]);
	}
}

void	ft_count_length(char *new_string, int *count, char c)
{
	(void)new_string;
	(void)c;
	(*count)++;
}

void	ft_copy_char(char *new_string, int *count, char c)
{
	(void)count;
	*new_string = c;
}
