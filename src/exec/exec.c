/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**duplicate_args(char **original_args)
{
	int		count;
	char	**new_args;
	int		i;

	if (!original_args)
		return (NULL);
	count = 0;
	while (original_args[count])
		count++;
	new_args = malloc((count + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		new_args[i] = ft_strdup(original_args[i]);
		if (!new_args[i])
		{
			while (i-- > 0)
				free(new_args[i]);
			return (free(new_args), NULL);
		}
	}
	new_args[count] = NULL;
	return (new_args);
}

static t_cmd_data	*interpreter(t_pars_data *cmd)
{
	t_cmd_data		*cmds;
	t_list			*lst;
	t_command_data	*cur;
	int				skip;
	int				fd_in;
	int				fd_out;
	char			**args;
	char			*path;
	t_cmd_data		*node;

	cmds = NULL;
	lst = cmd->commands;
	while (lst)
	{
		cur = (t_command_data *)lst->content;
		skip = 0;
		fd_in = open_infiles(cur->redir_in);
		if (fd_in == -1)
			skip = 1;
		fd_out = open_outfiles(cur->redir_out);
		if (fd_out == -1)
			skip = 1;
		if (!skip)
		{
			args = duplicate_args(cur->raw_args);
			expand_args_array(args, g_shell.env);
			path = find_path(args[0]);
			if (!path)
				path = ft_strdup(args[0]);
			node = cmd_new(args, path, fd_in, fd_out);
			cmd_add_back(&cmds, node);
		}
		lst = lst->next;
	}
	return (cmds);
}

static void	child_exit_error(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
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

static void	handle_exec_error(t_cmd_data *cmd)
{
	if (errno == ENOENT || (!cmd->next && cmd->args && strcmp(cmd->args[0],
				"Makefile") == 0))
	{
		printf("bash: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	else if (errno == EACCES)
	{
		printf("bash: %s: Permission denided\n", cmd->args[0]);
		exit(126);
	}
	else
	{
		perror("execve");
		exit(1);
	}
}

static void	child_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
	int	status;

	child_exit_error(exe, cmd, fds);
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
	else
	{
		execve(cmd->path, cmd->args, exe->envp);
		handle_exec_error(cmd);
	}
}

static void	parent_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
	if (exe->prev_pipe != -1)
	{
		close(exe->prev_pipe);
		exe->prev_pipe = -1;
	}
	if (fds[1] != -1)
		close(fds[1]);
	exe->prev_pipe = fds[0];
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

static void	free_cmd_list(t_cmd_data *cmd_list)
{
	t_cmd_data	*current;
	t_cmd_data	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
}

static bool	cas_execute(t_exe_data *exe, t_cmd_data *cmds)
{
	int	saved_status;

	if (!cmds)
		return (true);
	if (!cmds->next && cmds->args && is_env_builtin(cmds->args[0]))
	{
		saved_status = g_shell.exit_status;
		exec_builtin(cmds, exe);
		if (strcmp(cmds->args[0], "echo") == 0)
			g_shell.exit_status = saved_status;
		free_cmd_list(cmds);
		return (true);
	}
	if (!cmds->next && cmds->args && strcmp(cmds->args[0], "exit") == 0)
	{
		builtin_exit(cmds->args);
		free_cmd_list(cmds);
		write(STDOUT_FILENO, "exit\n", 5);
		g_shell.running = 0;
		return (true);
	}
	return (false);
}

static bool	cond_boucle(t_cmd_data *current, int fds[2])
{
	if (current->skip_cmd)
	{
		current = current->next;
		return (true);
	}
	if (current->next)
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

static void	last_status(t_cmd_data *current)
{
	int	last_status;
	int	status;

	last_status = 0;
	while (current)
	{
		if (!current->skip_cmd)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
		current = current->next;
	}
	g_shell.exit_status = last_status;
}

static void	execute_pipeline(t_exe_data *exe, t_pars_data *cmd)
{
	t_cmd_data	*cmds;
	t_cmd_data	*current;
	int			fds[2];

	cmds = interpreter(cmd);
	if (cas_execute(exe, cmds))
		return ;
	current = cmds;
	while (current)
	{
		if (cond_boucle(cmds, fds))
			continue ;
		current->pid = fork();
		if (current->pid < 0)
			exit_with_error("fork", 1);
		if (!current->pid)
			child_process(exe, current, fds);
		else
			parent_process(exe, current, fds);
		current = current->next;
	}
	current = cmds;
	last_status(current);
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
