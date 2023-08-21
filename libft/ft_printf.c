/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:39:20 by cmenke            #+#    #+#             */
/*   Updated: 2023/03/02 15:01:04 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//prints the unsigned nbr.
static void	ft_nbr(long unsigned int num, int *cnt, char *ba, unsigned int len)
{
	if (num >= len)
		ft_nbr(num / len, cnt, ba, len);
	write(1, &ba[num % len], 1);
	*cnt += 1;
}

//prints the signed nbr.
static void	ft_nbr_s(long int num, int *cnt, char *ba, unsigned int len)
{
	if (num < 0)
	{
		write(1, &"-", 1);
		*cnt += 1;
		num *= -1;
	}
	if (num >= len)
		ft_nbr(num / len, cnt, ba, len);
	write(1, &ba[num % len], 1);
	*cnt += 1;
}

//calls put_str or ft_nbr depending on the selected option.
static void	ft_print(char *s, int *cnt, int option)
{
	if (option == 0)
	{
		if (s != NULL)
		{
			ft_putstr_fd(s, 1);
			*cnt += ft_strlen(s);
		}
		else
		{
			ft_putstr_fd("(null)", 1);
			*cnt += 6;
		}
	}
	else if (option == 1)
	{
		write(1, &"0x", 2);
		*cnt += 2;
		ft_nbr((long unsigned int)s, cnt, "0123456789abcdef", 16);
	}
}

//checks for the difffernt identifiers and calls the corresponding function.
//returns -1 if no matching identifier was found.
static void	ft_cases(va_list arg_list, char c, int *cnt)
{
	if (c == 'c' || c == '%')
	{
		if (c == '%')
			ft_putchar_fd('%', 1);
		else
			ft_putchar_fd(va_arg(arg_list, int), 1);
		*cnt += 1;
	}
	else if (c == 's')
		ft_print(va_arg(arg_list, char *), cnt, 0);
	else if (c == 'p')
		ft_print(va_arg(arg_list, void *), cnt, 1);
	else if (c == 'd' || c == 'i')
		ft_nbr_s(va_arg(arg_list, int), cnt, "0123456789", 10);
	else if (c == 'u')
		ft_nbr_s(va_arg(arg_list, unsigned int), cnt, "0123456789", 10);
	else if (c == 'x')
		ft_nbr_s(va_arg(arg_list, unsigned int), cnt, "0123456789abcdef", 16);
	else if (c == 'X')
		ft_nbr_s(va_arg(arg_list, unsigned int), cnt, "0123456789ABCDEF", 16);
}

//iterates through the input and calls ft_cases if a '%' is found.
//else it prints the chars from the input string.
int	ft_printf(const char *input, ...)
{
	int		cnt;
	int		i;
	va_list	arg_list;

	i = -1;
	cnt = 0;
	va_start(arg_list, input);
	while (input[++i])
	{
		if (input[i] == '%')
			ft_cases(arg_list, input[++i], &cnt);
		else
		{
			ft_putchar_fd(input[i], 1);
			cnt += 1;
		}
	}
	va_end(arg_list);
	return (cnt);
}
