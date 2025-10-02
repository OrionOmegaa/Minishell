/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 19:21:38 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_data(t_env_data *env)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (env[++i].key != NULL)
	{
		free(env[i].key);
		free(env[i].value);
	}
	free(env);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static bool	path_in_args(t_cmd_data *cmd)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->path)
		return (false);
	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i] == cmd->path)
			return (true);
		i++;
	}
	return (false);
}

void	free_cmd(t_cmd_data *cmd)
{
	bool	in_args;
	int		i;

	if (!cmd)
		return ;
	in_args = path_in_args(cmd);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->path && !in_args)
		free(cmd->path);
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	free(cmd);
}

int	free_exe(t_exe_data *exe, int ret_val, int free_envp, char *err_msg)
{
	t_cmd_data	*tmp;
	int			i;

	while (exe->cmds)
	{
		tmp = exe->cmds->next;
		free_cmd(exe->cmds);
		exe->cmds = tmp;
	}
	if (free_envp && exe->envp)
	{
		i = 0;
		while (exe->envp[i])
			free(exe->envp[i++]);
		free(exe->envp);
	}
	if (err_msg)
		write(2, err_msg, strlen(err_msg));
	return (ret_val);
}
