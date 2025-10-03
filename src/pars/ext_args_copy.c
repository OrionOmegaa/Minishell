/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_args_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:43:04 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/03 14:47:05 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	change_quote(char s, bool *sq, bool *dq)
{
	if (s == '\'' && !(*sq))
	{
		*sq = !(*sq);
		if (!(*sq))
			return (true);
	}
	if (s == '"' && !(*dq))
	{
		*dq = !(*dq);
		if (!(*dq))
			return (true);
	}
	return (false);
}

static char	*return_func(char **res, int j)
{
	(*res)[j] = '\0';
	return (*res);
}

static bool	c(bool sq, bool dq, int i, int len)
{
	return (!sq && !dq && (i + 1 < len));
}

char	*copy_arg_content(const char *start, int len)
{
	char	*res;
	int		i;
	int		j;
	bool	sq;
	bool	dq;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	sq = false;
	dq = false;
	while ((++i) < len && j < len)
	{
		if (change_quote(start[i], &sq, &dq))
			res[j++] = '\x02';
		if (start[i] == '$' && sq)
			res[j++] = '\x01';
		if (start[i] == '$' && c(sq, dq, i, len) && is_quote(start[i + 1]))
			continue ;
		else
			res[j++] = start[i];
	}
	return (return_func(&res, j));
}
