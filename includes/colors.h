/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:18:07 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/16 01:36:34 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

//ESC[style;color_value_type;R;G;Bstop
//\x1B[38;2;255;0;204m"
# define STYLE_DEF "\033[0m"
# define BOLD_PINK "\033[1;38;2;255;0;204m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"

# define L_RED "\033[38;2;237;45;45m"

#endif