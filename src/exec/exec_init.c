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
    
    // Compte les éléments
    int count = 0;
    while ((*env)[count].key != NULL)
        count++;
    
    // Crée un tableau de pointeurs
    exe.env = malloc((count + 1) * sizeof(t_env_data *));
    for (int i = 0; i < count; i++)
        exe.env[i] = &((*env)[i]);  // ← Pointeur vers chaque structure
    exe.env[count] = NULL;
    
    exe.pars = pars;
    exe.prev_pipe = -1;
    exe.cmds = NULL;
    return (exe);
}

/* ORIGINAL
t_exe_data init_exe(t_env_data **env, t_pars_data *pars)
{
    t_exe_data exe;

    exe.pars = pars;
    exe.env = env;
    exe.prev_pipe = -1;
    exe.cmds = NULL;
    return (exe);
}*/

t_env_data *init_env(char **envp)
{
    t_env_data *env = NULL;
    for (int i = 0; envp[i]; i++)
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            size_t key_len = equal - envp[i];
            char *key = ft_strndup(envp[i], key_len);
            char *value = ft_strdup(equal + 1);
            env_set(&env, key, value);
            free(key);
            free(value);
        }
    }
    return (env);
}