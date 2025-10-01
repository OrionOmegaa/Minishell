/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:53:11 by mpoirier          #+#    #+#             */
/*   Updated: 2024/11/19 13:54:18 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_i(int num, size_t *counter)
{
	if (num == -2147483648)
	{
		ft_printf_i((num / 10), counter);
		ft_printf_c('8', counter);
	}
	else if (num < 0)
	{
		ft_printf_c('-', counter);
		ft_printf_i(-num, counter);
	}
	else
	{
		if (num > 9)
			ft_printf_i((num / 10), counter);
		ft_printf_c(('0' + num % 10), counter);
	}
}
