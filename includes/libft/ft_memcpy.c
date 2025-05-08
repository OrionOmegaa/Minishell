/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:13:35 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/08 10:41:20 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	ptr = (unsigned char *)src;
	ptr2 = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		ptr2[i] = ptr[i];
		i++;
	}
	return (dest);
}
