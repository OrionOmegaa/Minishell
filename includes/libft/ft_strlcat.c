/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:32:43 by mpoirier          #+#    #+#             */
/*   Updated: 2024/11/08 13:43:50 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (dst[i] && i < size)
		i++;
	j = 0;
	k = 0;
	while (src[j])
		j++;
	if (i == size)
		return (i + j);
	while (src[k] && i + k < size - 1)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[k + i] = '\0';
	return (i + j);
}
