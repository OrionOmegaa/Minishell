/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_export(char **args, t_exe_data *exe)
{
    int i = 0;
    if (!args[1])
    {
        int j = -1;
        while (exe->env[++j])
        {
            if (exe->env[j]->value)
                ft_printf("declare -x %s=\"%s\"\n", exe->env[j]->key, exe->env[j]->value);
            else
                ft_printf("declare -x %s\n", exe->env[j]->key);
        }
        return 0;
    }
    while (args[++i])
    {
        char *equal_sign = ft_strchr(args[i], '=');
        if (equal_sign)
        {
            size_t key_len = equal_sign - args[i];
            char key[256];
            char *value = equal_sign + 1;
            if (key_len >= sizeof(key))
            {
                ft_printf("export: variable name too long\n");
                i++;
                continue;
            }
            ft_memcpy(key, args[i], key_len);
            key[key_len] = '\0';
            exe->env = env_set((exe->env), key, value);
        }
        else
            env_set(exe->env, args[i], NULL);
    }
    return 0;
}

int builtin_unset(char **args, t_exe_data *exe)
{
    int i = 1;

    if (!args[1])
        return 0;
    while (args[i])
    {
        env_unset(exe->env, args[i]);
        i++;
    }
    return 0;
}

int builtin_env(t_exe_data *exe)
{
    int i;

    i = -1;
    if (!exe || !exe->env)
        return (1);
    while (exe->env[++i])
    {
        if (!exe->env[i]) 
        {
            //printf("DEBUG: exe->env[%d] est NULL, arrêt\n", i);
            break;
        }
        if (!exe->env[i]->key || !exe->env[i]->value)
        {
            //printf("DEBUG: exe->env[%d] key ou value NULL\n", i++);
            continue;
        }
        ft_printf("%s=%s\n", exe->env[i]->key, exe->env[i]->value);
    }
    return 0;
}

int builtin_exit(char **args)
{
    g_shell.exit_status= 0;
    if (args[1])
        g_shell.exit_status = ft_atoi(args[1]);
    g_shell.running = 0;
    return (g_shell.exit_status);
}
