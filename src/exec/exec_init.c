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

    exe.pars = pars;
    exe.env = env;
    exe.prev_pipe = -1;
    exe.cmds = NULL;
    return (exe);
}

t_env_data *init_env(char **envp)
{
    t_env_data *env = NULL;

    for (int i = 0; envp[i]; i++)
    {
        char *equal = strchr(envp[i], '=');
        if (equal)
        {
            size_t key_len = equal - envp[i];
            char *key = strndup(envp[i], key_len);
            char *value = ft_strdup(equal + 1);
            env_set(&env, key, value);
        }
    }
    return (env);
}