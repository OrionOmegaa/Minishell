/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_split_pipes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:42:11 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 23:00:50 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_segments(char *line)
{
	int		count;
	int		i;
	bool	in_q;
	char	q;

	count = 1;
	i = 0;
	in_q = false;
	q = 0;
	while (line[i])
	{
		update_quote(line[i], &in_q, &q);
		if (line[i] == '|' && !in_q)
			count++;
		i++;
	}
	return (count);
}

int	iterate_segments(char *line, char **cmds)
{
	return (iterate_segments_body(line, cmds));
}
