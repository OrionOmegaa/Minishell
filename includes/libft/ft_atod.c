/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:33:34 by hdescamp          #+#    #+#             */
/*   Updated: 2025/02/13 09:40:44 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	result;
	double	sign;
	double	decimal_place;

	result = 0.0;
	sign = 1.0;
	decimal_place = 1.0;
	while (*str == ' ')
		str++;
	if (*str++ == '-')
		sign = -1.0;
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			decimal_place /= 10.0;
			result += (*str++ - '0') * decimal_place;
		}
	}
	return (result * sign);
}
