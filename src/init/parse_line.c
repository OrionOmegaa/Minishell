/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_parse_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:22:45 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 21:23:23 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_command(t_pars_data *pars, char *seg)
{
	t_command_data	*cmd;
	t_list			*node;

	cmd = pars_single_command(seg);
	if (!cmd)
		return (-1);
	node = ft_lstnew(cmd);
	if (!node)
		return (free_command_data(cmd), -1);
	ft_lstadd_back(&pars->commands, node);
	return (0);
}

int	parse_command_line(t_pars_data *pars, char *line)
{
	char	**cmds;
	int		count;
	int		i;

	cmds = split_by_pipes(line, &count);
	if (!cmds)
		return (-1);
	i = 0;
	while (i < count)
	{
		if (cmds[i] && append_command(pars, cmds[i]) == -1)
		{
			while (cmds[i])
				free(cmds[i++]);
			free(cmds);
			return (-1);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
	return (0);
}
