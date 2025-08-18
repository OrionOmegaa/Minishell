/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:01:09 by hdescamp          #+#    #+#             */
/*   Updated: 2025/08/18 10:45:54 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	base_ten(int nb)
{
	int	d;

	d = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		d++;
	}
	return (d);
}

static char	*ft_limit(int n, char *str)
{
	if (n == 0)
		str = ft_strdup("0");
	if (n == -2147483648)
		str = ft_strdup("-2147483648\0");
	if (n == 2147483647)
		str = ft_strdup("2147483647\0");
	return (str);
}

static char	*ft_next(int *nb, int *size)
{
	char	*r;

	if (*nb < 0)
	{
		*size = base_ten(-(*nb)) + 1;
		r = (char *)malloc((*size + 1) * sizeof(char));
		if (!r)
			return (NULL);
		*nb = -(*nb);
		r[0] = '-';
	}
	else
	{
		*size = base_ten(*nb);
		r = (char *)malloc((*size + 1) * sizeof(char));
		if (!r)
			return (NULL);
	}
	return (r);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		s;
	int		i;

	str = NULL;
	if (n == 0 || n == -2147483648 || n == 2147483647)
	{
		str = ft_limit(n, str);
		if (!str)
			return (NULL);
		return (str);
	}
	str = ft_next(&n, &s);
	if (!str)
		return (NULL);
	str[s] = '\0';
	i = 0;
	while (i < s && n > 0)
	{
		str[s - i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (str);
}