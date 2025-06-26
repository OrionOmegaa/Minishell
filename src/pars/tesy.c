/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/06/26 13:56:36 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_known(t_env_data **env, char *key)
{
    int i;

    i = -1;
    while ((env)[++i])
    {
        if ((*env)[i].key == key)
            return (i);
    }
    return (-1);
}

static int  env_len(t_env_data **env)
{
    int len;
    
    len = 0;
    while (env[len])
        len++;
    return (len);
}

static t_env_data   **add_new_data(t_env_data **env, char *key, char *value)
{
    
}

void    env_set(t_env_data **env, char *key, char *value)
{
    int i;
    
    i = is_known(env, key);
    if (i != -1)
    {
        (*env)[i].value = value;
        return ;
    }
    env = add_new_data(env, key, value);
}