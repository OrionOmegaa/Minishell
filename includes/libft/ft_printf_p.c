/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:57:18 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/20 09:48:44 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_p(void *ptr, size_t *count)
{
	char			*str;
	unsigned long	ptr_address;

	ptr_address = (unsigned long)ptr;
	if (ptr == 0)
	{
		str = "(nil)";
		ft_printf_s(str, count);
	}
	else
	{
		ft_printf_s("0x", count);
		str = ft_aux_pf(ptr_address, HEX_LOW);
		ft_printf_s(str, count);
		free(str);
	}
}
