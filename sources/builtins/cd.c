/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:49:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 18:20:40 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_target_path(char **arguments, t_list *env_list,
				char **target_path);
static void	ft_update_oldpwd(t_list *oldpwd, t_list *pwd,
				bool *print_quotes_for_oldpwd, char *cwd_old);
static bool	ft_change_working_directory(char *target_path);
static bool	ft_update_pwd(t_list *pwd);

int	ft_cd(char **arguments, t_list *env_list, bool *print_quotes_for_oldpwd)
{
	char	*target_path;
	t_list	*pwd;
	t_list	*oldpwd;
	char	*cwd_old;
	int		status;

	cwd_old = NULL;
	status = __success;
	status = ft_get_target_path(arguments, env_list, &target_path);
	if (status)
		return (status);
	oldpwd = ft_find_env_variable("OLDPWD", env_list);
	pwd = ft_find_env_variable("PWD", env_list);
	if (!ft_get_current_working_directory(&cwd_old))
		return (__system_call_error);
	if (!ft_change_working_directory(target_path))
		return (ft_free_ptr_and_set_to_null((void **)&cwd_old), __mini_error);
	ft_update_oldpwd(oldpwd, pwd, print_quotes_for_oldpwd, cwd_old);
	if (!ft_update_pwd(pwd))
		return (__system_call_error);
	return (__success);
}

static int	ft_get_target_path(char **arguments, t_list *env_list,
		char **target_path)
{
	t_list	*home;

	if (!arguments[1])
	{
		home = ft_find_env_variable("HOME", env_list);
		if (!home)
		{
			ft_print_error_message("cd: HOME not set", NULL, NULL, NULL);
			return (__mini_error);
		}
		else if (!((t_env *)home->content)->value)
			return (__success_but_stop);
		else
			*target_path = ((t_env *)home->content)->value;
	}
	else
		*target_path = arguments[1];
	return (__success);
}

static void	ft_update_oldpwd(t_list *oldpwd, t_list *pwd,
			bool *print_quotes_for_oldpwd, char *cwd_old)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;

	if (oldpwd)
		oldpwd_env = (t_env *)oldpwd->content;
	if (oldpwd && pwd)
	{
		pwd_env = (t_env *)pwd->content;
		ft_assign(oldpwd_env, NULL, pwd_env->value, true);
		pwd_env->value = NULL;
	}
	else if (oldpwd && !pwd && *print_quotes_for_oldpwd)
	{
		ft_assign(oldpwd_env, NULL, NULL, true);
		*print_quotes_for_oldpwd = false;
	}
	else if (oldpwd)
		ft_assign(oldpwd_env, NULL, cwd_old, true);
	ft_free_ptr_and_set_to_null((void **)&cwd_old);
}

static bool	ft_change_working_directory(char *target_path)
{
	if (chdir(target_path) == -1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": cd: ", 2);
		perror(target_path);
		return (false);
	}
	return (true);
}

static bool	ft_update_pwd(t_list *pwd)
{
	char	*cwd_buf;

	cwd_buf = NULL;
	if (pwd)
	{
		if (!ft_get_current_working_directory(&cwd_buf))
			return (false);
		ft_assign((t_env *)pwd->content, NULL, cwd_buf, "");
	}
	return (true);
}
