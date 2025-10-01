/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:16:36 by mpoirier          #+#    #+#             */
/*   Updated: 2024/11/14 15:23:17 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source;
	size_t				i;

	i = 0;
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (dest < source)
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	else
	{
		while (0 < len)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	return (dst);
}
