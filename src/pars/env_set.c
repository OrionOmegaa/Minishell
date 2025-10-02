/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 14:22:59 by mpoirier         ###   ########.fr       */
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
	t_env_data	*new_env;

	new_env = malloc(sizeof(t_env_data) * (len + 2));
	if (!new_env)
		return ;
	ft_bzero(new_env, sizeof(t_env_data) * (len + 2));
	if (*env)
	{
		len = -1;
		while ((*env)[++len].key != NULL)
		{
			new_env[len].key = (*env)[len].key;
			new_env[len].value = (*env)[len].value;
		}
		free(*env);
	}
	new_env[len].key = ft_strdup(key);
	if (value)
		new_env[len].value = ft_strdup(value);
	else
		new_env[len].value = NULL;
	new_env[len + 1].key = NULL;
	new_env[len + 1].value = NULL;
	*env = new_env;
}

// Needs to be tested, did some pretty heavy modifications here. Leo :D
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
		if (!value)
			(*env)[i].value = NULL;
		else
			(*env)[i].value = ft_strdup(value);
		return (env);
	}
	len = env_len(*env);
	realloc_env(env, len, key, value);
	return (env);
}

static void	env_copy(t_env_data **env, char *key, int len, int i)
{
	t_env_data	*res;
	
	res = malloc(sizeof(t_env_data) * (len + 1));
	if (!res || !*env)
		return ;
	ft_bzero(res, sizeof(t_env_data) * (len + 1));
	len = 0;
	while((*env)[++i].key != NULL)
	{
		if(ft_strncmp((*env)[i].key, key, ft_strlen(key)) != 0)
		{
			res[len].key = (*env)[i].key;
			res[len++].value = (*env)[i].value;
		}
		else
		{
			free((*env)[i].key);
			free((*env)[i].value);
		}
	}
	res[len].key = NULL;
	res[len].value = NULL;
	free(*env);
	(*env) = res;
}

t_env_data	**env_unset(t_env_data **env, char *key)
{
	if (!env || !*env || !key)
		return (NULL);
	if (is_known(env, key) == -1)
		return (NULL);
	env_copy(env, key, env_len(*env), -1);
	if (!env)
		return (NULL);
	return (env);
}
