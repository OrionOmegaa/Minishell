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

static char **duplicate_args(char **original_args)
{
    if (!original_args)
        return NULL;
    int count = 0;
    while (original_args[count])
        count++;
    /*printf("DEBUG DUPLICATE: %d args à dupliquer\n", count);
    for (int k = 0; k < count; k++)
        printf("DEBUG DUPLICATE IN: [%d] = '%s' (len=%zu)\n", k, original_args[k], strlen(original_args[k]));
    */char **new_args = malloc((count + 1) * sizeof(char *));
    if (!new_args)
        return NULL;
    for (int i = 0; i < count; i++)
    {
        new_args[i] = ft_strdup(original_args[i]);
        //printf("DEBUG DUPLICATE OUT: [%d] = '%s' (len=%zu)\n", i, new_args[i] ? new_args[i] : "NULL", new_args[i] ? strlen(new_args[i]) : 0);
        if (!new_args[i])
        {
            for (int j = 0; j < i; j++)
                free(new_args[j]);
            free(new_args);
            return NULL;
        }
    }
    new_args[count] = NULL;
    return new_args;
}

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
            char **args = duplicate_args(cur->raw_args);
            expand_args_array(args, &g_shell.env);
            char *path = find_path(args[0]);
            if (!path)
                path = ft_strdup(args[0]);
            //printf("DEBUG FINAL FD: cmd='%s', final_fd_in=%d, final_fd_out=%d\n", args[0], fd_in, fd_out);
            t_cmd_data *node = cmd_new(args, path, fd_in, fd_out);
            cmd_add_back(&cmds, node);
        }
        lst = lst->next;
    }
    return (cmds);
}

static void child_process(t_exe_data *exe, t_cmd_data *cmd, int fds[2])
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
    if (exe->prev_pipe != -1)
        close(exe->prev_pipe);
    if (fds[0] != -1)
        close(fds[0]);
    if (fds[1] != -1)
        close(fds[1]);
    if (is_builtin(cmd->args[0]))
    {
        //printf("DEBUG: '%s' détecté comme builtin\n", cmd->args[0]);
        int status = exec_builtin(cmd, exe);
        //printf("DEBUG: builtin '%s' retourne %d\n", cmd->args[0], status);
        exit(status);
    }
    else
    {
        //printf("DEBUG: '%s' pas builtin, execve avec path='%s'\n", cmd->args[0], cmd->path);
        execve(cmd->path, cmd->args, exe->envp);
        if (errno == ENOENT)
            printf("bash: %s: command not found\n", cmd->args[0]);
        else if (errno == EACCES)
            printf("bash: %s: Permission denided\n", cmd->args[0]);
        else
            perror("execve");
        //printf("DEBUG: about to exit(127)\n");
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
    if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
        close(cmd->fd_in);
    if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
        close(cmd->fd_out);
}

static void  free_cmd_list(t_cmd_data *cmd_list)
{
    t_cmd_data *current = cmd_list;
    t_cmd_data *next;
    
    while (current)
    {
        next = current->next;
        free_cmd(current);
        current = next;
    }
}

static void    execute_pipeline(t_exe_data *exe, t_pars_data *cmd)
{
    t_cmd_data *cmds;
    t_cmd_data *current;
    int fds[2];

    cmds = interpreter(cmd);
    if (!cmds)
        return ;
    if (!cmds->next && cmds->args && is_env_builtin(cmds->args[0]))
    {
        int saved_status = g_shell.exit_status;
        exec_builtin(cmds, exe);
        if (strcmp(cmds->args[0], "echo") == 0)
            g_shell.exit_status = saved_status;
        free_cmd_list(cmds);
        return ;
    }
    if (!cmds->next && cmds->args && strcmp(cmds->args[0], "exit") == 0)
    {
        builtin_exit(cmds->args);
        free_cmd_list(cmds);
        g_shell.running = 0;
        return ;
    }
    current = cmds;
    while (current)
    {
        if (current->skip_cmd)
        {
            current = current->next;
            continue;
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
    int last_status = 0;
    while (current)
    {
        if (!current->skip_cmd)
        {
            int status;
            waitpid(current->pid, &status, 0);
            if (WIFEXITED(status))
                last_status = WEXITSTATUS(status);
        }
        current = current->next;
    }
    g_shell.exit_status = last_status;
    free_cmd_list(cmds);
}

int executor(t_env_data **env, t_pars_data *pars)
{
    t_exe_data exe;

    exe = init_exe(env, pars);
    execute_pipeline(&exe, exe.pars);
    *env = *(exe.env);
    free_exe(&exe, 0, 0, NULL);
    return (0);
}

