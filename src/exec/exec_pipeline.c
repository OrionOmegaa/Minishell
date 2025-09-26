/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refactor <refactor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:01 by refactor          #+#    #+#             */
/*   Updated: 2025/09/26 17:30:01 by refactor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	execute_single_builtin(t_exe_data *exe, t_cmd_data *cmds)
{
	int	saved;

	if (cmds->next || !cmds->args || !is_env_builtin(cmds->args[0]))
		return (false);
	saved = g_shell.exit_status;
	exec_builtin(cmds, exe);
	if (!strcmp(cmds->args[0], "echo"))
		g_shell.exit_status = saved;
	free_cmd_list(cmds);
	return (true);
}

static bool	execute_single_exit(t_cmd_data *cmds)
{
	if (cmds->next || !cmds->args || strcmp(cmds->args[0], "exit"))
		return (false);
	builtin_exit(cmds->args);
	free_cmd_list(cmds);
	write(STDOUT_FILENO, "exit\n", 5);
	g_shell.running = 0;
	return (true);
}

static bool	prepare_fds(t_cmd_data *cur, int fds[2])
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
