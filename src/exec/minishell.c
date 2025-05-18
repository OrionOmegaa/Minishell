/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

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

char **split_args(char *input)
{
    int     argc;
    char    **args;
    int     i;
    int     j;

    argc = count_args(input);
    args = malloc(sizeof(char *) * (argc + 1));
    i = 0;
    j = 0;
    while (*input && i < argc)
    {
        while (*input == ' ' || *input == '\t')
            input++;
        char *start = input;
        while (*input && *input != ' ' && *input != '\t')
            input++;
        int len = input - start;
        args[i] = malloc(len + 1);
        while (j < len)
        {
            args[i][j] = start[j];
            j++;
        }
        args[i][len] = '\0';
        i++;
    }
    args[i] = NULL;
    return args;
}

void free_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

char *find_command_path(char *cmd)
{
    char    buffer[4096];
    char    *res;
    char    *path;
    char    *start;
    int     i;
    int     len;
    int     j;
    int     k;
    int     m;

    i = 0;
    if (!cmd)
        return NULL;

    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return cmd;
        return NULL;
    }
    path = getenv("PATH");
    if (!path)
        return NULL;
    while (*path)
    {
        start = path;
        while (*path && *path != ':')
            path++;
        len = path - start;
        i = 0;
        while (i < len && i < 4096 - 1)
        {
            buffer[i] = start[i];
            i++;
        }
        buffer[i] = '\0';
        j = 0;
        while (buffer[j]) j++;
        buffer[j++] = '/';
        k = 0;
        while (cmd[k] && j < 4096 - 1)
            buffer[j++] = cmd[k++];
        buffer[j] = '\0';
        if (access(buffer, X_OK) == 0)
        {
            res = malloc(j + 1);
            m = 0;
            while (m <= j)
            {
                res[m] = buffer[m];
                m++;
            }
            return res;
        }
        if (*path == ':')
            path++;
    }
    return NULL;
}

void execute_command(char *input)
{
    char    **args;
    pid_t   pid;
    char    *cmd_path;
    int     status;

    args = split_args(input);
    pid = fork();
    if (!args || !args[0])
        return;
    if (strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        exit(0);
    }
    if (pid == 0)
    {
        cmd_path = find_command_path(args[0]);
        if (!cmd_path)
        {
            write(2, "Commande introuvable\n", 22);
            exit(127);
        }
        execve(cmd_path, args, environ);
        perror("execve");
        exit(1);
    } 
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
        perror("fork");
    free_args(args);
}

int main()
{
    char    *line;

    while (1) {
        line = readline("Minishell> ");
        if (!line)
            break;
        if (*line)
            add_history(line);
        execute_command(line);
        free(line);
    }
    return 0;
}
