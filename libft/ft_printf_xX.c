/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:56 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/19 14:51:33 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_xx(unsigned int num, size_t *count, char *base)
{
	char	*str;

	str = ft_aux_pf(num, base);
	ft_printf_s(str, count);
	free(str);
}
