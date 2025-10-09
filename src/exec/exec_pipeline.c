/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:01 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/07 19:01:11 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_process(t_exe_data *exe, t_cmd_data *cur, int fds[2], t_shell *my_shell)
{
	cur->pid = fork();
	if (cur->pid < 0)
		exit_with_error("fork", 1);
	if (!cur->pid)
		child_process(exe, cur, fds, my_shell);
	else
		parent_process(exe, cur, fds);
}

static void	execute_pipeline(t_exe_data *exe, t_pars_data *pars, t_shell *my_shell)
{
	t_cmd_data	*cmds;
	t_cmd_data	*cur;
	int			fds[2];

	cmds = interpreter(pars, my_shell);
	if (!cmds)
		return ;
	if (execute_single_builtin(exe, cmds, my_shell)
		|| execute_single_exit(cmds, my_shell))
		return ;
	cur = cmds;
	while (cur)
	{
		if (prepare_fds(cur, fds))
		{
			cur = cur->next;
			continue ;
		}
		fork_process(exe, cur, fds, my_shell);
		cur = cur->next;
	}
	last_status(cmds, my_shell);
	free_cmd_list(cmds);
}

int	executor(t_shell *my_shell, t_pars_data *pars)
{
	t_exe_data	exe;

	exe = init_exe((*my_shell).env, pars);
	execute_pipeline(&exe, exe.pars, my_shell);
	free_exe(&exe, 0, 1, NULL);
	return (0);
}
