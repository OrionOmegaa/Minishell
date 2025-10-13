/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:57:21 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 16:50:47 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

static int	is_env_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", INT_MAX) == 0)
		return (1);
	return (0);
}

bool	execute_single_builtin(t_exe_data *exe, t_cmd_data *cmds,
	t_shell *my_shell)
{
	int	saved;

	if (cmds->next || !cmds->args || !is_env_builtin(cmds->args[0]))
		return (false);
	saved = (*my_shell).exit_status;
	exec_builtin(cmds, exe, my_shell);
	if (!strcmp(cmds->args[0], "echo"))
		(*my_shell).exit_status = saved;
	free_cmd_list(cmds);
	return (true);
}

bool	execute_single_exit(t_cmd_data *cmds, t_shell *my_shell)
{
	if (cmds->next || !cmds->args || strcmp(cmds->args[0], "exit"))
		return (false);
	builtin_exit(cmds->args, my_shell);
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
