/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:57:21 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/06 16:38:58 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	execute_single_builtin(t_exe_data *exe, t_cmd_data *cmds, t_shell *my_shell)
{
	int	saved;

	if (cmds->next || !cmds->args || !is_env_builtin(cmds->args[0]))
		return (false);
	saved = (*my_shell).exit_status;
	exec_builtin(cmds, exe);
	if (!strcmp(cmds->args[0], "echo"))
		(*my_shell).exit_status = saved;
	free_cmd_list(cmds);
	return (true);
}

bool	execute_single_exit(t_cmd_data *cmds, t_shell *my_shell)
{
	if (cmds->next || !cmds->args || strcmp(cmds->args[0], "exit"))
		return (false);
	builtin_exit(cmds->args);
	free_cmd_list(cmds);
	write(STDOUT_FILENO, "exit\n", 5);
	(*my_shell).running = 0;
	return (true);
}

bool	prepare_fds(t_cmd_data *cur, int fds[2])
{
	if (cur->skip_cmd)
		return (true);
	if (cur->next)
	{
		if (pipe(fds) < 0)
			exit_with_error("pipe", 1);
	}
	else
	{
		fds[0] = -1;
		fds[1] = -1;
	}
	return (false);
}
