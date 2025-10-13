/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_split_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:31 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 21:32:37 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

int	is_redirect_char(char c)
{
	return (c == '<' || c == '>');
}

char	**split_by_pipes(char *line, int *cmd_count)
{
	char	**cmds;

	*cmd_count = count_segments(line);
	cmds = malloc(sizeof(char *) * (*cmd_count + 1));
	if (!cmds)
		return (NULL);
	if (iterate_segments(line, cmds) == -1)
	{
		ft_free_tab(cmds);
		return (NULL);
	}
	cmds[*cmd_count] = NULL;
	return (cmds);
}
