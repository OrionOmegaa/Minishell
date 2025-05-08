/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:47:04 by hdescamp          #+#    #+#             */
/*   Updated: 2024/12/03 11:47:06 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ftt_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	res = malloc(sizeof(char) * (ftt_strlen(s1) + ftt_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}

char	*ftt_strchr(const char *string, int searched_char )
{
	char	*str;

	str = (char *)string;
	while (*str != searched_char && *str != 0)
		str++;
	if (*str == searched_char)
		return (str);
	else
		return (NULL);
}

void	ftt_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ftt_calloc(size_t element_count, size_t element_size)
{
	char	*res;

	res = malloc(element_size * element_count);
	if (!res)
		return (NULL);
	ftt_bzero(res, element_size * element_count);
	return (res);
}

size_t	ftt_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
