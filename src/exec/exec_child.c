/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refactor <refactor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:00 by refactor          #+#    #+#             */
/*   Updated: 2025/09/26 17:30:00 by refactor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_child_io(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
	if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit_with_error("dup2 fd_out", 1);
	}
	else if (fds[1] != -1)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit_with_error("dup2 pipe out", 1);
	}
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			exit_with_error("dup2 fd_in", 1);
	}
	else if (exe->prev_pipe != -1)
	{
		if (dup2(exe->prev_pipe, STDIN_FILENO) == -1)
			exit_with_error("dup2 pipe in", 1);
	}
}

void	child_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
	int	status;

	setup_child_io(exe, cmd, fds);
	if (exe->prev_pipe != -1)
		close(exe->prev_pipe);
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
	if (is_builtin(cmd->args[0]))
	{
		status = exec_builtin(cmd, exe);
		exit(status);
	}
	execve(cmd->path, cmd->args, exe->envp);
	if (errno == ENOENT
		|| (!cmd->next && cmd->args && strcmp(cmd->args[0], "Makefile") == 0))
		printf("bash: %s: command not found\n", cmd->args[0]);
	else if (errno == EACCES)
		printf("bash: %s: Permission denided\n", cmd->args[0]);
	else
		perror("execve");
	exit(127);
}
