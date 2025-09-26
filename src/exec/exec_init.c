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

t_exe_data	init_exe(t_env_data **env, t_pars_data *pars)
{
	t_exe_data	exe;

	exe.env = env;
	exe.pars = pars;
	exe.prev_pipe = -1;
	exe.cmds = NULL;
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
