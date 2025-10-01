/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_pars_single_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:24 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 21:32:37 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	psc_handle_redir(char *s, int i, t_command_data *cmd);
int	psc_copy_plain(char *src, char *dst, int i, int *j);

static void	fill_clean(char *src, char *clean, t_command_data *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '<' || src[i] == '>')
			i = psc_handle_redir(src, i, cmd);
		else
			i = psc_copy_plain(src, clean, i, &j);
	}
	clean[j] = '\0';
}

t_command_data	*pars_single_command(char *cmd_str)
{
	t_command_data	*cmd;
	char			*clean;

	while (*cmd_str && (*cmd_str == ' ' || *cmd_str == '\t'))
		cmd_str++;
	if (!*cmd_str)
		return (NULL);
	cmd = new_command_data();
	if (!cmd)
		return (NULL);
	clean = malloc(ft_strlen(cmd_str) + 1);
	if (!clean)
		return (free(cmd), NULL);
	fill_clean(cmd_str, clean, cmd);
	cmd->raw_args = extract_args(clean);
	free(clean);
	if (!cmd->raw_args)
		return (free_command_data(cmd), NULL);
	return (cmd);
}
