/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:46:50 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 12:02:03 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_minisell_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint_in_minishell);
}

void	ft_restore_default_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	ft_set_singals_in_parent_during_execution(void)
{
	signal(SIGQUIT, ft_handle_sigquit_in_parent_during_execution);
	signal(SIGINT, ft_handle_sigint_in_parent_during_execution);
}
