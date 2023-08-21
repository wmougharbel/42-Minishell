/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:50:05 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 21:07:02 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

/// @brief The main struct that holds all the data for the shell
/// @details
/// @exit_code: the exit code of the last command
/// @default_stdin:
/// @default_stdout:
/// @print_quotes_for_oldpwd: if true, oldpwd="" will be printed one time if set
/// @add_no_quotes: if true, no quotes will be added to the expanded variable
// value for proterction
/// @cmd_line: the command line that the user entered
/// @envp_array: the environment variables from the env_list
/// @pipe_fds:
/// @process_ids:
/// @heredocs: the names of the heredoc_files that are needed for <<
/// @cmd_sequences: the command blocks separated by pipes -> cmd1 | cmd2 | cmd3
/// @all_tokens: all the tokens from the tokenized command line
/// @env_list: the environment variables in a linked list
/// it stores the original ones from the envp and the new ones from export

typedef struct s_shell_data
{
	int		exit_code;
	int		default_stdin;
	int		default_stdout;
	bool	print_quotes_for_oldpwd;
	bool	add_no_quotes;
	bool	in_child_process;
	bool	waiting_for_process;
	char	*cmd_line;
	char	**envp_array;
	int		**pipe_fds;
	pid_t	*process_ids;
	char	**heredocs;
	t_list	*cmd_sequences;
	t_list	*all_tokens;
	t_list	*env_list;
}				t_shell_data;

/// @brief The struct that holds the data for each command block
/// @details
/// @tokens: the tokens of the command block; same memory as in all_tokens
/// @envp_command_paths: the paths of the PATH variable in the envp_array
/// @command_path: the path of the command to be executed
/// @args: the arguments of the command; same memory as in tokens
/// @input_fd:
/// @output_fd:
typedef struct s_command_sequences
{
	t_list	*tokens;
	char	**envp_command_paths;
	char	*command_path;
	char	**args;
	int		input_fd;
	int		output_fd;
}				t_cmd_sequences;

/// @brief The struct that holds the tokens
/// @details
/// @token: the token string itself
/// @type: the type of the token
/// @heredoc_number: used to acces the heredoc_file name in the heredocs array
typedef struct s_tokens
{
	char	*token;
	char	type;
	int		heredoc_number;
}				t_tokens;

/// @brief The struct that holds the environment variables
/// @details
/// @name: the name of the variable
/// @value: the value of the variable
/// @print_empty_quotes: if true, empty quotes will be printed as value; var=""
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			print_empty_quotes;
}				t_env;

enum e_token_type
{
	text,
	syntax_error,
	pipe_operator,
	redirection_in,
	redirection_in_heredoc,
	redirection_out_trunc,
	redirection_out_append,
	redirection_filename
};

enum	e_error_codes
{
	__success,
	__no_history,
	__syntax_error,
	__system_call_error,
	__stop_execution,
	__mini_error,
	__no_builtin_found,
	__success_but_stop,
	__general_syntax_error
};

enum e_variable_expansion_cases
{
	v_keep_dollar,
	v_exit_code,
	v_no_trim,
	v_trim
};

#endif
