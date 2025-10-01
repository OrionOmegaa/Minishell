/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:45:35 by mpoirier          #+#    #+#             */
/*   Updated: 2024/11/08 12:38:15 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;
	int		pos;
	int		pos2;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	pos = 0;
	pos2 = 0;
	tab = malloc(sizeof(char) * (i + j + 1));
	if (tab == NULL)
		return (NULL);
	while (pos != i + j)
	{
		if (pos >= i)
			tab[pos] = s2[pos2++];
		else
			tab[pos] = s1[pos];
		pos++;
	}
	tab[pos] = '\0';
	return (tab);
}
