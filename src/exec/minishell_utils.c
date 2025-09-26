/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_args(char *input)
{
    int count;
    int in_word;

    count = 0;
    in_word = 0;
    while (*input)
    {
        if (*input == ' ' || *input == '\t')
            in_word = 0;
        else if (!in_word)
        {
            count++;
            in_word = 1;
        }
        input++;
    }
    return count;
}

void exit_with_error(const char *msg, int code)
{
    perror(msg);
    exit(code);
}

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

static bool path_in_args(t_cmd_data *cmd)
{
    bool path_in_args;
    int i;
    int j;

    path_in_args = false;
    if (cmd->args && cmd->path)
    {
        j = -1;
        while (cmd->args[++j])
        {
            if (cmd->args[j] == cmd->path)
            {
                path_in_args = true;
                break;
            }
        }
    }
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[++i])
            free(cmd->args[i]);
        free(cmd->args);
    }
    return (path_in_args);
}

void free_cmd(t_cmd_data *cmd)
{
    if (!cmd)
        return;
    if (cmd->args && cmd->path && cmd->args[0] == cmd->path)
        exit(1);
    if (cmd->path && !path_in_args())
        free(cmd->path);
    if (cmd->fd_in > 2)
        close(cmd->fd_in);
    if (cmd->fd_out > 2)
        close(cmd->fd_out);
    free(cmd);
}

int free_exe(t_exe_data *exe, int ret_val, int free_envp, char *err_msg)
{
    t_cmd_data *tmp;

    while (exe->cmds)
    {
        tmp = exe->cmds->next;
        free_cmd(exe->cmds);
        exe->cmds = tmp;
    }
    if (free_envp && exe->envp)
    {
        int i = 0;
        while (exe->envp[i])
            free(exe->envp[i++]);
        free(exe->envp);
    }
    // exe->env is a handle allocated in init_env; do not free here (cleanup_shell owns it)
    if (err_msg)
        write(2, err_msg, strlen(err_msg));
    return ret_val;
}
