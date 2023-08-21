/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:52:58 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 21:26:27 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_store_env_in_list(char **env, t_list **env_list);
static int	ft_prepare_env_variables(t_shell_data *shell_data);
static bool	increase_shlvl(t_list **env_list);

int	ft_prepare_minishell(t_shell_data **shell_data, char **envp)
{
	g_signal_number = 0;
	*shell_data = ft_calloc(1, sizeof(t_shell_data));
	if (!*shell_data)
		return (perror("shell_data struct allocation error"), exit(1), 1);
	if (!ft_store_env_in_list(envp, &(*shell_data)->env_list))
		return (ft_free_shell_data(*shell_data, true), exit(1), 1);
	if (ft_prepare_env_variables(*shell_data) == __system_call_error)
		return (ft_free_shell_data(*shell_data, true), exit(1), 1);
	ft_set_minisell_signals();
	return (0);
}

static bool	ft_store_env_in_list(char **env, t_list **env_list)
{
	int		i;

	if (!env)
		return (true);
	i = 0;
	while (env[i])
	{
		if (ft_update_or_add_env_variable(env[i],
				env_list, NULL, NULL) == __system_call_error)
			return (ft_putendl_fd("error storing env in list\n", 2), false);
		i++;
	}
	return (true);
}

static int	ft_prepare_env_variables(t_shell_data *shell_data)
{
	char	*pwd_name;
	char	*pwd_value;

	pwd_value = NULL;
	if (!increase_shlvl(&shell_data->env_list))
		return (__system_call_error);
	if (ft_update_or_add_env_variable("OLDPWD", &shell_data->env_list,
			NULL, NULL) == __system_call_error)
		return (__system_call_error);
	if (!ft_find_env_variable("PWD", shell_data->env_list))
	{
		pwd_name = ft_strdup("PWD");
		if (!pwd_name)
			return (perror("error creating pwd_name"), __system_call_error);
		ft_pwd(&pwd_value, false);
		if (ft_update_or_add_env_variable(NULL, &shell_data->env_list,
				pwd_name, pwd_value) == __system_call_error)
			return (__system_call_error);
	}
	return (__success);
}

static bool	increase_shlvl(t_list **env_list)
{
	t_list	*shlvl;
	char	*name;
	char	*value;

	name = ft_strdup("SHLVL");
	if (!name)
		return (perror("error creating name - SHLVL"), false);
	shlvl = ft_find_env_variable("SHLVL", *env_list);
	if (!shlvl || !((t_env *)shlvl->content)->value)
	{
		value = ft_strdup("1");
		if (!value)
			return (free(name), perror("error creating SHLVL - 1"), false);
		if (!store_var_in_node(env_list, name, value, true))
			return (free(name), free(value), false);
		return (true);
	}
	value = ft_itoa(ft_atoi(((t_env *)shlvl->content)->value) + 1);
	if (!value)
		return (free(name), perror("error creating SHLVL Value + 1"), false);
	ft_assign((t_env *)shlvl->content, name, value, true);
	return (true);
}
