/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/13 19:00:54 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void print_env(t_env_data *env)
{
    int i;

    if (!env) {
        printf("env = NULL\n");
        return ;
    }
    i = 0;
    while (env[i].key != NULL) {
        // printf("ici\n");
        printf("env[%d]: key = %s, value = %s\n", i, env[i].key, env[i].value);
        i++;
    }
}*/

static int is_known(t_env_data **env, char *key)
{
    int i;

    i = -1;
    while ((*env)[++i].key != NULL)
    {
        if (ft_strncmp((*env)[i].key, key, ft_strlen(key)) == 0)
            return (i);
    }
    return (-1);
}

static int  env_len(t_env_data *env)
{
    int len;
    
    len = 0;
    while (env[len].key != NULL)
        len++;
    return (len);
}

void    env_set(t_env_data **env, char *key, char *value)
{
    int i;
    int len;
    
    if (!*env)
    {
        (*env) = (t_env_data *)malloc(1 * sizeof(t_env_data));
        if (!*env)
            return ;
        (*env)[0].key = NULL; 
    }
    i = is_known(env, key);
    if (i != -1)
    {
        (*env)[i].value = value;
        return ;
    }
    len = (env_len(*env) + 1);
    *env = (t_env_data *)ft_realloc((void *)*env, (len * sizeof(t_env_data)) , ((len + 1) * sizeof(t_env_data)));
    (*env)[len - 1].key = key;
    (*env)[len - 1].value = value;
    (*env)[len].key = NULL;
    (*env)[len].value = NULL;
}

static t_env_data *env_copy(t_env_data *env, int size, char *key)
{
    t_env_data *res = malloc(size * sizeof(t_env_data));
    int i = 0;
    int j = 0;

    while (i < size && env[i].key != NULL)
    {
        if (ft_strncmp(env[i].key, key, ft_strlen(key)) == 0)
            i += 1;
        if (i < size && env[i].key != NULL) {
            res[j].key = env[i].key;
            res[j].value = env[i].value;
            j++;
        }
        i++;
    }
    if (j < size) {
        res[j].key = NULL;
        res[j].value = NULL;
    }
    return (res);
}

void    env_unset(t_env_data **env, char *key)
{
    if (!env || !*env)
        return (env_set(env, NULL, NULL));
    else if (!key) // key == NULL
    {
        free (*env);
        return ;
    }
    else if (is_known(*env, key) == -1)
        return ;
    int len = env_len(*env);
    t_env_data *res = (env_copy((*env), len + 1, key));
    free(*env);
    *env = res;
}