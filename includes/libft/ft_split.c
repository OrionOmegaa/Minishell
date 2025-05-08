/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:00:52 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/14 16:13:29 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_charset(char c, char charset)
{
	if (charset == c)
		return (1);
	return (0);
}

static int	ft_len(const char *str, char c)
{
	int	i;
	int	l;

	l = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			l++;
		i++;
	}
	return (l);
}

static int	ft_word_len(const char *str, char c)
{
	int	l;
	int	i;

	l = 0;
	i = -1;
	while (str[++i] && !is_charset(str[i], c))
		++l;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		l;
	int		i;
	int		j;

	tab = (char **)malloc(sizeof(char *) * (ft_len(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < ft_len(s, c))
	{
		while (s[i] && is_charset(s[i], c))
			++i;
		l = ft_word_len(s + i, c);
		tab[j] = (char *)malloc(sizeof(char) * (l + 1));
		if (!tab[j])
			return (NULL);
		ft_strlcpy(tab[j++], s + i, l + 1);
		i += l;
	}
	tab[j] = NULL;
	return (tab);
}
