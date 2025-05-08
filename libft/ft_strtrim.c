/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:01:05 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/08 15:21:01 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_trim_s(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_set(s1[i], set))
		i++;
	return (i);
}

static int	ft_trim_e(const char *s1, const char *set)
{
	int	len;

	len = 0;
	while (s1[len])
		len++;
	len--;
	while (len >= 0 && ft_set(s1[len], set))
		len--;
	return (len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	int		i;
	int		j;
	int		k;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	j = ft_trim_s(s1, set);
	k = ft_trim_e(s1, set);
	if (j >= k)
		return (ft_strdup(""));
	tab = malloc(sizeof(char) * (k - j + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (j < k)
		tab[i++] = s1[j++];
	tab[i] = '\0';
	return (tab);
}
