/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:47:42 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 22:19:05 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//general
# include <errno.h>
# include <limits.h>
# include <sys/param.h>
# include <stdio.h>
# include <stdbool.h>
//readline
# include <readline/readline.h>
# include <readline/history.h>
//signals
# include <signal.h>
//open
# include <fcntl.h>
//Wait functions
# include <sys/types.h>
# include <sys/wait.h>
//lstat
# include <sys/stat.h>

//custom
# include "../libft/libft.h"
# include "structs.h"
# include "builtins.h"
# include "colors.h"

# define SHELL_NAME "minishell"
# define PROMPT "minishell:$ "
//permission for open
# define RW_R__R__ 0644

extern int	g_signal_number;

//main
int		ft_process_command_line(t_shell_data *shell_data);
void	ft_exit_ctrl_d(t_shell_data *shell_data);
//prepare_minishell.c
int		ft_prepare_minishell(t_shell_data **shell_data, char **envp);
//print_error.c
void	ft_print_error_message(char *part1, char *part2,
			char *part3, char *part4);

//signals
	//set_signals_functions.c
void	ft_set_minisell_signals(void);
void	ft_restore_default_signals(void);
void	ft_set_singals_in_parent_during_execution(void);
	//signal_handlers.c
void	ft_handle_sigint_in_parent_during_execution(int sig_num);
void	ft_handle_sigquit_in_parent_during_execution(int sig_num);
void	ft_handle_sigint_in_minishell(int sig_num);
//lexer
	//tokenize_command_line.c
int		ft_tokenize_command_line(char *cmd_line, t_list **tokens);
	// tokenize_command_line_helpers.c
void	ft_skip_to_next_non_delimiter(char **command_line);
bool	ft_is_whitespace(char c);
void	ft_skip_quote_block(char **string, bool	only_single_quotes,
			bool end_with_quote);
void	ft_move_while_same_char(char **command_line, char c);
	//set_token_types.c
void	ft_assign_token_type(void *node);
	// syntax_error.c
bool	ft_is_equal_quote_ammount(char *s);
bool	ft_is_syntax_error_in_tokens(t_list *tokens);
	//heredoc
int		ft_handle_heredocs(t_shell_data *shell_data);
	// heredoc_file_creation_deletion.c
bool	ft_create_heredoc_files(t_shell_data *shell_data);
void	ft_delete_heredoc_files(char **heredoc_files);
	// heredoc_helpers.c
bool	ft_is_quotes_in_delimiter(char *string);

	//split_in_sequences.c
int		ft_split_tokens_in_sequences(t_list *tokens, t_list **cmd_sequences);
	//variable_expansion.c
bool	ft_expand_variables_in_tokens(t_list **tokens,
			t_shell_data *shell_data);
bool	ft_expand_variables_in_string(char **string, t_shell_data *shell_data,
			bool ignore_quotes);
	//variable_expansion_utils.c
bool	protect_value(char **value, int expansion_case);
void	ft_cut_out_node(t_list **tokens, t_list *previous,
			t_list *current, t_list *next);
void	ft_update_quote_state(bool *in_single_quotes,
			bool *in_double_quotes, char c);
void	ft_skip_whitespace(char *string, int *i);
bool	ft_is_char_quote(char c);
	//variable_expansion_trim_value.c
bool	ft_trim_value(char **string);
	//variable_expansion_get_name_value.c
bool	ft_get_variable_name(char *string, char **variable_name);
bool	ft_get_variable_value(char *name, char **value, t_list *env_list);
bool	ft_get_exit_code_string(char **name, char **value,
			t_shell_data *shell_data);
	//redirection.c
int		ft_handle_redirection_operators(t_cmd_sequences *sequence,
			t_list *tokens, char **heredocs);
	//token_list_to_char_array
bool	ft_token_list_to_args_array(char ***arguments, t_list *tokens);
	//remove_quotes
bool	ft_remove_quotes_from_tokens(t_list *tokens);
bool	ft_remove_quotes_from_string(char **string);
void	ft_count_length(char *new_string, int *count, char c);
void	ft_copy_char(char *new_string, int *count, char c);
// clearing
	//ft_free_double_pointer.c
void	ft_free_double_pointer_char(char ***ptr);
void	ft_free_double_pointer_int(int ***ptr, int size);
void	ft_free_ptr_and_set_to_null(void **ptr);
	// clear_all.c
void	ft_clear_token(void *token);
void	ft_clear_command_sequence(void *sequence);
	//clear_structs
void	ft_free_shell_data(t_shell_data *shell_data, bool everything);
void	ft_clear_command_sequence(void *node);
void	ft_clear_token(void *node);
void	ft_clear_env_variable(void *node);
//execution
	//invoke_close_functions
int		get_builtin_command(t_shell_data *shell_data,
			t_cmd_sequences *sequence_to_execute, char *command,
			int status);
	//check_file
bool	ft_is_file_existent(char *command, t_shell_data *shell_data);
bool	ft_is_directory(char *command, t_shell_data *shell_data);
bool	ft_is_executable(char *command, t_shell_data *shell_data);
bool	ft_search_in_env_paths_for_cmd(t_shell_data *shell_data,
			t_cmd_sequences *sequence_to_execute);
bool	ft_check_file(char *command, t_shell_data *shell_data);

	//create_processes
int		ft_execute_commands(t_shell_data *shell_data);
bool	ft_create_pipes(t_shell_data *shell_data, int number_of_pipes);
bool	ft_fork_child_processes(t_shell_data *shell_data,
			int number_of_commands);
void	ft_wait_for_childs_and_get_exit_code(t_shell_data *shell_data,
			int number_of_commands);
void	ft_get_exit_code(int *exit_code, int stat_loc, bool first_encounter,
			bool reset_signal_number);
	//execute_coammand_in_child
void	ft_execute_command_in_child(t_shell_data *shell_data,
			int number_of_commands, t_cmd_sequences *sequence_to_execute,
			int command_index);
int		ft_execution_of_command(t_shell_data *shell_data,
			t_cmd_sequences *sequence_to_execute, bool single_builtin);
int		ft_execute_builtin_if_builtin(t_shell_data *shell_data,
			t_cmd_sequences *sequence_to_execute);
	//check_if_cmd_is_valid
bool	ft_is_cmd_valid(t_shell_data *shell_data,
			t_cmd_sequences *sequence_to_execute);
	//single_builtin_execution
int		ft_execute_single_builtin(t_shell_data *shell_data,
			int number_of_commands, t_cmd_sequences *sequence_to_execute,
			int command_index);
bool	ft_is_builtin(t_cmd_sequences *sequence_to_execute);
	//duplication_of_fds_in_child
bool	ft_duplication_of_fds(int **pipe_fds,
			t_cmd_sequences *sequence_to_execute, int number_of_commands,
			int command_index);
bool	ft_input_redirection_in_child(int **pipe_fds, int input_fd,
			int command_index);
bool	ft_output_redirection_in_child(int **pipe_fds, int output_fd,
			int number_of_commands, int command_index);
void	ft_close_all_pipes(int **pipe_fds, int number_of_pipes);
	//get_envp_cmd_paths
bool	ft_get_cmd_path(char **envp_paths, char *cmd, char **cmd_path);
bool	ft_get_envp_paths(char **envp, char ***envp_paths);
	//env_list_to_char_array
bool	ft_env_list_to_envp_array(t_shell_data *shell_data);
char	*ft_create_one_env_variable(t_env *one_variable);

// //delete!!!!
// //helpers.c
// 	// void ft_print_list(t_list *list);
// void	ft_print_token_list(t_list *tokens);
// void	ft_print_command_sequences(t_list *cmd_sequences);
// void	ft_print_tokens_and_type(t_list *tokens);//
// void	ft_print_command_sequences_args(t_list *cmd_sequences);/////////////
// void	ft_print_double_array(char **array);
// void	ft_print_envp_array(char **envp_array);
// void	ft_print_pipe_fds(int **pipe_fds, int number_of_pipes);
// void	ft_print_command_sequences(t_list *cmd_sequences);
// void	ft_print_token_list(t_list *tokens);
// void	ft_print_double_array(char **array);
// void	ft_print_command_sequences_args(t_list *cmd_sequences);
// //delete them
// void	ft_print_tokens_and_type(t_list *tokens);

#endif