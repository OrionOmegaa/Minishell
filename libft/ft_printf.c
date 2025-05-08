/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:45:55 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/20 10:43:53 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_sort(va_list va, char *str, size_t *count)
{
	if (*str == 'c')
		ft_printf_c(va_arg(va, int), count);
	else if (*str == 's')
		ft_printf_s(va_arg(va, char *), count);
	else if (*str == 'p')
		ft_printf_p(va_arg(va, void *), count);
	else if (*str == 'd')
		ft_printf_d(va_arg(va, int), count);
	else if (*str == 'i')
		ft_printf_i(va_arg(va, int), count);
	else if (*str == 'u')
		ft_printf_u(va_arg(va, unsigned int), count);
	else if (*str == 'x')
		ft_printf_xx(va_arg(va, unsigned int), count, HEX_LOW);
	else if (*str == 'X')
		ft_printf_xx(va_arg(va, unsigned int), count, HEX_UP);
	else if (*str == '%')
		ft_printf_c(*str, count);
}

int	ft_printf(const char *str, ...)
{
	va_list	va;
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_sort(va, (char *)str, &count);
		}
		else
			ft_printf_c(*str, &count);
		str++;
	}
	va_end(va);
	return (count);
}
