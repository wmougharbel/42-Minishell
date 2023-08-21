/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_cmd_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:24:19 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 03:26:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_add_slash_to_envp_paths(char ***envp_paths);

//checks if the cmd is to be found in one of the paths specified by envp
bool	ft_get_cmd_path(char **envp_paths, char *cmd, char **cmd_path)
{
	int		i;

	*cmd_path = NULL;
	i = 0;
	while (envp_paths && envp_paths[i] && cmd)
	{
		*cmd_path = ft_strjoin(envp_paths[i], cmd);
		if (!*cmd_path)
			return (perror("error - join cmd to path"), false);
		if (access(*cmd_path, X_OK) == 0)
			return (true);
		else
			ft_free_ptr_and_set_to_null((void **)cmd_path);
		i++;
	}
	return (true);
}

bool	ft_get_envp_paths(char **envp, char ***envp_paths)
{
	int		i;
	char	*path_string;

	path_string = NULL;
	*envp_paths = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_string = envp[i] + 5;
		i++;
	}
	if (path_string)
		*envp_paths = ft_split(path_string, ':');
	if (path_string && !*envp_paths)
		return (perror("error splitting envp paths"), false);
	if (*envp_paths && !ft_add_slash_to_envp_paths(envp_paths))
		return (ft_free_double_pointer_char(envp_paths), false);
	return (true);
}

static bool	ft_add_slash_to_envp_paths(char ***envp_paths)
{
	char	**result;
	int		i;

	i = 0;
	while ((*envp_paths)[i])
		i++;
	result = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!result)
		return (perror("error - creating new paths array to add slash"), false);
	i = 0;
	while ((*envp_paths)[i])
	{
		result[i] = ft_strjoin((*envp_paths)[i], "/");
		if (!result[i])
			return (perror("error - join slash to envp_paths"),
				ft_free_double_pointer_char(&result), false);
		i++;
	}
	ft_free_double_pointer_char(envp_paths);
	*envp_paths = result;
	return (true);
}
