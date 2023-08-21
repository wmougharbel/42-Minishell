/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:15:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/06 19:58:03 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exit_code(char *str, bool *print_exit);
static bool	ft_get_number(char *str, int *exit_code);

int	ft_exit(char **args, t_shell_data *shell_data)
{
	int		exit_code;
	bool	print_exit;

	print_exit = true;
	if (!args[1])
		shell_data->exit_code = 0;
	else if (args[2])
	{
		printf("exit\n");
		ft_print_error_message("exit:", " too many arguments", NULL, NULL);
		shell_data->exit_code = 1;
		return (__stop_execution);
	}
	else
		shell_data->exit_code = ft_exit_code(args[1], &print_exit);
	if (!shell_data->in_child_process)
	{
		if (print_exit)
			printf("exit\n");
		rl_clear_history();
		exit_code = shell_data->exit_code;
		ft_free_shell_data(shell_data, true);
		exit(exit_code);
	}
	return (__stop_execution);
}

static int	ft_exit_code(char *str, bool *print_exit)
{
	int	exit_code;

	if (ft_get_number(str, &exit_code))
		;
	else
	{
		*print_exit = false;
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" : numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	return (exit_code);
}

static bool	ft_get_number(char *str, int *exit_code)
{
	unsigned long int	temp;
	unsigned long int	result;
	int					minus;

	minus = 1;
	result = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			minus = -1;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		temp = result * 10 + (*str++ - '0');
		if ((minus == 1 && temp > 9223372036854775807)
			|| (minus == -1 && temp > 9223372036854775808U))
			return (false);
		result = temp;
	}
	*exit_code = (int)(result * minus);
	return (true);
}
