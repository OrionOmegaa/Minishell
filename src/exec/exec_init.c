/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 15:33:12 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **init_envp(t_env_data *env)
{
	char **envp;
	char *value;
	int i;
	int len;
	
	if (!env)
		return (NULL);
	envp = malloc(sizeof(char *) * (env_len(env)+ 1));
	if (!envp)
		return (NULL);
	i = -1;
	while (env[++i].key != NULL)
	{
		len = ft_strlen(env[i].key);
		value = env[i].value;
		envp[i] = malloc(len + ft_strlen(value) + 2);
		if (!envp[i])
			return (NULL);
		ft_strlcpy(envp[i], env[i].key, len);
		envp[i][len] = '=';
		ft_strlcpy(envp[i] + len + 1, value, ft_strlen(value));
	}
	envp[i] = NULL;
	return (envp);
}

t_exe_data	init_exe(t_env_data **env, t_pars_data *pars)
{
	t_exe_data	exe;

	exe.env = env;
	exe.pars = pars;
	exe.prev_pipe = -1;
	exe.cmds = NULL;
	exe.envp = init_envp(*env);
	return (exe);
}

static t_env_data	**free_error(t_env_data *arr, int count)
{
	int	j;

	j = -1;
	while ((++j) < count)
	{
		free((arr)[j].key);
		free((arr)[j].value);
	}
	free(arr);
	return (NULL);
}

static t_env_data	*boucle_init_env(char **envp, t_env_data *arr, int count)
{
	int		i;
	char	*equal;
	size_t	key_len;

	i = -1;
	while ((++i) < count)
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key_len = (size_t)(equal - envp[i]);
			arr[i].key = ft_strndup(envp[i], key_len);
			arr[i].value = ft_strdup(equal + 1);
		}
		else
		{
			arr[i].key = ft_strdup(envp[i]);
			arr[i].value = NULL;
		}
		if (!arr[i].key)
			return (*(free_error(arr, count)));
	}
	arr[count].key = NULL;
	arr[count].value = NULL;
	return (arr);
}

t_env_data	**init_env(char **envp)
{
	int			count;
	t_env_data	*arr;
	t_env_data	**handle;

	count = 0;
	while (envp[count])
		count++;
	arr = (t_env_data *)malloc(sizeof(t_env_data) * (count + 1));
	if (!arr)
		return (NULL);
	arr = boucle_init_env(envp, arr, count);
	handle = (t_env_data **)malloc(sizeof(t_env_data *));
	if (!handle)
		return (free_error(arr, count));
	*handle = arr;
	return (handle);
}
