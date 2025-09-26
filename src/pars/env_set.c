/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 09:37:32 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_known(t_env_data **env, char *key)
{
	int	i;

	i = -1;
	while ((*env)[++i].key != NULL)
	{
		if (ft_strncmp((*env)[i].key, key, ft_strlen(key)) == 0
			&& ft_strlen((*env)[i].key) == ft_strlen(key))
			return (i);
	}
	return (-1);
}

int	env_len(t_env_data *env)
{
	int	len;

	len = 0;
	while (env[len].key != NULL)
		len++;
	return (len);
}

void	realloc_env(t_env_data **env, int len, char *key, char *value)
{
	*env = ft_realloc(*env, len * sizeof(t_env_data), (len + 1)
			* sizeof(t_env_data));
	if (!*env)
		return ;
	(*env)[len - 1].key = ft_strdup(key);
	if (!value)
		(*env)[len - 1].value = NULL;
	else
		(*env)[len - 1].value = ft_strdup(value);
}

// A tester, j'ai aussi changer des trucs je suis pas certain. Leo :D
t_env_data	**env_set(t_env_data **env, char *key, char *value)
{
	int	i;
	int	len;

	if (!*env)
	{
		*env = ft_calloc(1, sizeof(t_env_data));
		if (!*env)
			return (NULL);
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
	len = env_len(*env);
	realloc_env(env, len, key, value);
	return (env);
}

// Norme à faire
static t_env_data	*env_copy(t_env_data *env, char *key)
{
	t_env_data	*res;
	int			i;
	int			j;

	res = malloc(sizeof(t_env_data) * (env_len(env)));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (env[++i].key != NULL)
	{
		if (ft_strncmp(env[i].key, key, ft_strlen(key)) != 0
			|| ft_strlen(env[i].key) != ft_strlen(key))
		{
			res[j].key = env[i].key;
			res[j++].value = env[i].value;
		}
		else
		{
			free(env[i].key);
			free(env[i].value);
		}
	}
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
