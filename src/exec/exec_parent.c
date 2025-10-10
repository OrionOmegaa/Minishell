/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:01 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/09 15:48:38 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
	if (exe->prev_pipe != -1)
		close(exe->prev_pipe);
	if (fds[1] != -1)
		close(fds[1]);
	exe->prev_pipe = fds[0];
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

void	free_cmd_list(t_cmd_data *lst)
{
	t_cmd_data	*next;

	while (lst)
	{
		next = lst->next;
		free_cmd(lst);
		lst = next;
	}
}

void	last_status(t_cmd_data *cur, t_shell *my_shell)
{
	int	status;
	int	last;

	last = 0;
	while (cur)
	{
		if (!cur->skip_cmd)
		{
			while (waitpid(cur->pid, &status, 0) < 0)
				;
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
		}
		cur = cur->next;
	}
	(*my_shell).exit_status = last;
}
