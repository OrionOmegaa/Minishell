/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd_data *interpreter(t_pars_data *cmd)
{
    t_cmd_data *cmds = NULL;
    t_list *lst = cmd->commands;
    while (lst)
    {
        t_command_data *cur = (t_command_data *)lst->content;
        int skip = 0;
        int fd_in = open_infiles(cur->redir_in);
        if (fd_in == -1)
            skip = 1;
        int fd_out = open_outfiles(cur->redir_out);
        if (fd_out == -1)
            skip = 1;
        if (!skip)
        {
            char **args = extract_args(cur->raw_args);
            char *path = find_path(args[0]);
            if (!path)
                path = args[0];
            t_cmd_data *node = cmd_new(args, path, fd_in, fd_out);
            cmd_add_back(&cmds, node);
        }
        lst = lst->next;
    }
    return (cmds);
}

static void child_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
    if (cmd->fd_in != -1)
    {
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
            exit_with_error("dup2 fd_in", 1);
    }
    else if (exe->prev_pipe != -1)
    {
        if (dup2(exe->prev_pipe, STDIN_FILENO) == -1)
            exit_with_error("dup2 pipe in", 1);
    }
    if (cmd->fd_out != -1)
    {
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            exit_with_error("dup2 fd_out", 1);
    }
    else if (fds[1] != -1)
    {
        if (dup2(fds[1], STDOUT_FILENO) == -1)
            exit_with_error("dup2 pipe out", 1);
    }
    if (exe->prev_pipe != -1)
        close(exe->prev_pipe);
    if (fds[0] != -1)
        close(fds[0]);
    if (fds[1] != -1)
        close(fds[1]);
    if (is_builtin(cmd->args[0]))
    {
        int status = exec_builtin(cmd, exe);
        exit(status);
    }
    else
    {
        execve(cmd->path, cmd->args, exe->envp);
        perror("execve");
        exit(127);
    }
}

static void parent_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
{
    if (exe->prev_pipe != -1)
    {
        close(exe->prev_pipe);
        exe->prev_pipe = -1;
    }
    if (fds[1] != -1)
        close(fds[1]);
    exe->prev_pipe = fds[0];
    if (cmd->fd_in != -1)
        close(cmd->fd_in);
    if (cmd->fd_out != -1)
        close(cmd->fd_out);
}

static void    execute_pipeline(t_exe_data *exe, t_pars_data *cmd)
{
    t_cmd_data *cmds;
    int fds[2];

    cmds = interpreter(cmd);
    while (cmds)
    {
        if (cmds->skip_cmd)
        {
            cmds = cmds->next;
            continue;
        }
        if (pipe(fds) < 0)
            exit_with_error("pipe", 1);
        else if (!cmds->next)
        {
            fds[0] = -1;
            fds[1] = -1;
        }
        cmds->pid = fork();
        if (cmds->pid < 0)
            exit_with_error("fork", 1);
        if (!cmds->pid)
            child_process(exe, cmds, fds);
        else
            parent_process(exe, cmds, fds);
        cmds = cmds->next;
    }
    cmds = exe->cmds;
    while (cmds)
    {
        if (!cmds->skip_cmd)
            waitpid(cmds->pid, NULL, 0);
        cmds = cmds->next;
    }
}
    
int    executor(t_env_data **env, t_pars_data *pars)
{
    t_exe_data    exe;

    exe = init_exe(env, pars);
    execute_pipeline(&exe, exe.pars);
    return (free_exe(&exe, 0, 0, NULL));
}
