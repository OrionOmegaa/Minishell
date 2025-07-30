/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/30 14:17:04 by mpoirier         ###   ########.fr       */
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

int is_known(t_env_data **env, char *key)
{
    int i;

    i = -1;
    while ((*env)[++i].key != NULL)
    {
        if (ft_strncmp((*env)[i].key, key, ft_strlen(key)) == 0 && ft_strlen((*env)[i].key) == ft_strlen(key))
            return (i);
    }
    return (-1);
}

int  env_len(t_env_data *env)
{
    int len;
    
    len = 0;
    while (env[len].key != NULL)
        len++;
    return (len);
}

t_env_data	**env_set(t_env_data **env, char *key, char *value)
{
	int	i;
	int	len;

	if (!*env)
	{
		*env = malloc(sizeof(t_env_data));
		if (!*env)
			return (NULL);
		(*env)[0].key = NULL;
		(*env)[0].value = NULL;
	}
	if (!key)
		return (NULL);
	i = is_known(env, key);
	if (i != -1)
	{
		free((*env)[i].value);
		(*env)[i].value = ft_strdup(value);
		return (env);
	}
	len = env_len(*env) + 1;
	*env = ft_realloc(*env, len * sizeof(t_env_data), 
		(len + 1) * sizeof(t_env_data));
	if (!*env)
		return (NULL);
	(*env)[len - 1].key = ft_strdup(key);
	if (!value)
		(*env)[len - 1].value = NULL;
	else
		(*env)[len - 1].value = ft_strdup(value);
	(*env)[len].key = NULL;
	(*env)[len].value = NULL;
	return (env);
}

static t_env_data	*env_copy(t_env_data *env, char *key)
{
	t_env_data	*res;
	int			i;
	int			j;
	int			size;

	size = env_len(env);
	res = malloc(sizeof(t_env_data) * size);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i].key != NULL)
	{
		if (ft_strncmp(env[i].key, key, ft_strlen(key)) != 0 
			|| ft_strlen(env[i].key) != ft_strlen(key))
		{
			res[j].key = env[i].key;
			res[j].value = env[i].value;
			j++;
		}
		else
		{
			free(env[i].key);
			free(env[i].value);
		}
		i++;
	}
	res[j].key = NULL;
	res[j].value = NULL;
	return (res);
}

t_env_data	**env_unset(t_env_data **env, char *key)
{
	t_env_data	*res;

	if (!env || !*env || !key)
		return (NULL);
	if (is_known(env, key) == -1)
		return (NULL);
	res = env_copy(*env, key);
	if (!res)
		return (NULL);
	free(*env);
	*env = res;
	return (env);
}