/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:22:36 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 21:22:38 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pars_data	*init_pars_data(char *line)
{
	t_pars_data	*pars;

	if (!line || !*line)
		return (NULL);
	if (check_syntax_errors(line))
	{
		g_shell.exit_status = 2;
		return (NULL);
	}
	pars = malloc(sizeof(t_pars_data));
	if (!pars)
		return (NULL);
	pars->commands = NULL;
	if (parse_command_line(pars, line) == -1)
		return (free_pars_data(pars), NULL);
	return (pars);
}
