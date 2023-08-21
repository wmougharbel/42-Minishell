/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 19:07:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

//cd
int		ft_cd(char **arguments, t_list *env_list,
			bool *print_quotes_for_oldpwd);
//echo
void	ft_echo(char **command);
//env
void	ft_print_env_list(t_list *env_list);
//exit
int		ft_exit(char **args, t_shell_data *shell_data);
//export
	//export_create_name_value.c
bool	ft_create_name_and_value(char *argument, char **name,
			char **value, bool *print_empty_quotes);
	//export_print_list.c
int		print_export(t_list **env_list);
	//export
int		ft_export(char **arguemnts, t_list **env_list);
int		ft_update_or_add_env_variable(char *argument, t_list **env_list,
			char *name, char *value);
bool	ft_is_syntax_error_in_env_name(char *string);
bool	store_var_in_node(t_list **env_list, char *name,
			char *value, bool print_empty_quotes);
void	ft_assign(t_env *env_variable,
			char *name, char *value, bool print_empty_quotes);
//pwd
int		ft_pwd(char **pwd, bool print);
void	ft_print_pwd_and_free(char *path);
//unset
int		ft_unset(char **arguments, t_list **env_list_new,
			t_shell_data *shell_data);
//utils.c
t_list	*ft_find_env_variable(char *argument, t_list *env_list);
void	ft_free_name_and_value(char **name, char **value);
bool	ft_get_current_working_directory(char **cwd_buf);

#endif