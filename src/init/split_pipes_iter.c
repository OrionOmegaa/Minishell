/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_split_pipes_iter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:12:31 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 22:12:31 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote(char c, bool *in_q, char *q)
{
	if (is_quote(c) && !*in_q)
	{
		*in_q = true;
		*q = c;
	}
	else if (c == *q && *in_q)
		*in_q = false;
}

static char	*dup_seg(char *line, int start, int end)
{
	return (ft_substr(line, start, end - start));
}

static int	store_seg(char **arr, char *line, int idx, int span[2])
{
	arr[idx] = dup_seg(line, span[0], span[1]);
	if (!arr[idx])
		return (-1);
	if (arr[idx][0] == '\0')
	{
		free(arr[idx]);
		arr[idx] = NULL;
	}
	return (0);
}

static int	add_segment(char **cmds, char *line, int *seg, int span[2])
{
	if (store_seg(cmds, line, *seg, span) == -1)
		return (-1);
	(*seg)++;
	span[0] = span[1] + 1;
	return (0);
}

int	iterate_segments_body(char *line, char **cmds)
{
	int		span[2];
	int		i;
	int		seg;
	bool	in_q;
	char	q;

	span[0] = 0;
	i = 0;
	seg = 0;
	in_q = false;
	q = 0;
	while (line[i])
	{
		update_quote(line[i], &in_q, &q);
		if (line[i] == '|' && !in_q)
		{
			span[1] = i;
			if (add_segment(cmds, line, &seg, span) == -1)
				return (-1);
		}
		i++;
	}
	span[1] = i;
	return (store_seg(cmds, line, seg, span));
}
