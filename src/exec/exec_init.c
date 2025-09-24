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
    
    int count = 0;
    while (env[count] != NULL)
        count++;
    exe.env = malloc((count + 1) * sizeof(t_env_data *));
    for (int i = 0; i < count; i++)
        exe.env[i] = env[i];
    exe.env[count] = NULL;
    
    exe.pars = pars;
    exe.prev_pipe = -1;
    exe.cmds = NULL;
    return (exe);
}

t_env_data **init_env(char **envp)
{
    int count = 0;
    while (envp[count])
        count++;
    t_env_data **env = malloc((count + 1) * sizeof(t_env_data *));
    if (!env)
        return NULL;
    int i = -1;
    while (++i < count)
    {
        env[i] = malloc(sizeof(t_env_data));
        if (!env[i])
        {
            while (i > 0)
                free(env[--i]);
            free(env);
            return NULL;
        }
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            *equal = '\0';
            env[i]->key = ft_strdup(envp[i]);
            env[i]->value = ft_strdup(equal + 1);
            *equal = '=';
        }
    }
    env[count] = NULL;
    return (env);
}