/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_printf("%s\n", cwd);
        return 0;
    }
    perror("pwd");
    return (1);
}

int builtin_cd(char **args, t_exe_data *exe)
{
    char *path;

    if (!args[1])
        path = getenv("HOME");
    else
        path = args[1];
    if (!path)
    {
        ft_putendl_fd("cd: HOME not set", 2);
        return 1;
    }
    if (chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        env_set(exe->env, "PWD", cwd);
    return 0;
}

int builtin_echo(char **args)
{
    int i = 1;
    int no_newline = 0;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        int j = 1;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')
            break;
        no_newline = 1;
        i++;
    }
    while (args[i])
    {
        ft_printf("%s", args[i]);
        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    if (!no_newline)
        ft_printf("\n");
    return 0;
}

int exec_builtin(t_cmd_data *cmd, t_exe_data *exe)
{
    char *builtin = cmd->args[0];

    if (ft_strncmp(builtin, "echo", 5) == 0)
        return builtin_echo(cmd->args);
    else if (ft_strncmp(builtin, "cd", 3) == 0)
        return builtin_cd(cmd->args, exe);
    else if (ft_strncmp(builtin, "pwd", 4) == 0)
        return builtin_pwd();
    else if (ft_strncmp(builtin, "export", 7) == 0)
        return builtin_export(cmd->args, exe);
    else if (ft_strncmp(builtin, "unset", 6) == 0)
        return builtin_unset(cmd->args, exe);
    else if (ft_strncmp(builtin, "env", 4) == 0)
        return builtin_env(exe);
    else if (ft_strncmp(builtin, "exit", 5) == 0)
        return builtin_exit(cmd->args);
    return -1;
}

int is_env_builtin(const char *cmd)
{
    if (!cmd)
        return 0;
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return 1;
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return 1;
    if (ft_strncmp(cmd, "export", 7) == 0)
        return 1;
    return 0;
}

int is_builtin(const char *cmd)
{
    if (!cmd)
        return 0;
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return 1;
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return 1;
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return 1;
    if (ft_strncmp(cmd, "export", 7) == 0)
        return 1;
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return 1;
    if (ft_strncmp(cmd, "env", 4) == 0)
        return 1;
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return 1;
    return 0;
}