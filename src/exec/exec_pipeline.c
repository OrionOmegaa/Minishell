/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:01 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 20:57:18 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_process(t_exe_data *exe, t_cmd_data *cur, int fds[2])
{
	cur->pid = fork();
	if (cur->pid < 0)
		exit_with_error("fork", 1);
	if (!cur->pid)
		child_process(exe, cur, fds);
	else
		parent_process(exe, cur, fds);
}

void	execute_pipeline(t_exe_data *exe, t_pars_data *pars)
{
	t_cmd_data	*cmds;
	t_cmd_data	*cur;
	int			fds[2];

	cmds = interpreter(pars);
	if (!cmds)
		return ;
	if (execute_single_builtin(exe, cmds) || execute_single_exit(cmds))
		return ;
	cur = cmds;
	while (cur)
	{
		if (prepare_fds(cur, fds))
		{
			cur = cur->next;
			continue ;
		}
		fork_process(exe, cur, fds);
		cur = cur->next;
	}
	last_status(cmds);
	free_cmd_list(cmds);
}

int	executor(t_env_data **env, t_pars_data *pars)
{
	t_exe_data	exe;

	exe = init_exe(env, pars);
	execute_pipeline(&exe, exe.pars);
	free_exe(&exe, 0, 0, NULL);
	return (0);
}
