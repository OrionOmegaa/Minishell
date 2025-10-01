/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:06:46 by mpoirier          #+#    #+#             */
/*   Updated: 2024/11/20 09:45:55 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(char c, size_t *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_printf_s(char *str, size_t *count)
{
	if (!str)
		str = "(null)";
	while (*str)
		ft_printf_c(*str++, count);
}
