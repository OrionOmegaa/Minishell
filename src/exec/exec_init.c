/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exe_data init_exe(t_env_data **env, t_pars_data *pars)
{
    t_exe_data exe;

    // Keep a reference to the env handle (so env_set/env_unset can reallocate)
    exe.env = env;
    exe.pars = pars;
    exe.prev_pipe = -1;
    exe.cmds = NULL;
    return (exe);
}

t_env_data **init_env(char **envp)
{
    int         count;
    t_env_data  *arr;
    t_env_data  **handle;

    count = 0;
    while (envp[count])
        count++;
    arr = (t_env_data *)malloc(sizeof(t_env_data) * (count + 1));
    if (!arr)
        return (NULL);
    for (int i = 0; i < count; i++)
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            size_t key_len = (size_t)(equal - envp[i]);
            arr[i].key = ft_strndup(envp[i], key_len);
            arr[i].value = ft_strdup(equal + 1);
        }
        else
        {
            arr[i].key = ft_strdup(envp[i]);
            arr[i].value = NULL;
        }
        if (!arr[i].key)
        {
            // best-effort cleanup on partial failure
            for (int j = 0; j < i; j++)
            {
                free(arr[j].key);
                free(arr[j].value);
            }
            free(arr);
            return (NULL);
        }
    }
    arr[count].key = NULL;
    arr[count].value = NULL;
    handle = (t_env_data **)malloc(sizeof(t_env_data *));
    if (!handle)
    {
        for (int j = 0; j < count; j++)
        {
            free(arr[j].key);
            free(arr[j].value);
        }
        free(arr);
        return (NULL);
    }
    *handle = arr;
    return (handle);
}
