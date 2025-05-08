/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:01:21 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/19 14:03:20 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_d(int num, size_t *count)
{
	if (num == -2147483648)
	{
		ft_printf_d((num / 10), count);
		ft_printf_c('8', count);
	}
	else if (num < 0)
	{
		ft_printf_c('-', count);
		ft_printf_d(-num, count);
	}
	else
	{
		if (num > 9)
			ft_printf_d((num / 10), count);
		ft_printf_c(('0' + num % 10), count);
	}
}
