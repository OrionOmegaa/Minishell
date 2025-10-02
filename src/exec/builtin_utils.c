/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 14:35:13 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    sort_env(t_env_data **env)
{
    int   i;
    int   j;
    t_env_data  tmp;

    for (i = 0; (*env)[i].key != NULL; i++)
    {
        for (j = i + 1; (*env)[j].key != NULL; j++)
        {
            if (ft_strncmp((*env)[i].key, (*env)[j].key, ft_strlen((*env)[i].key)) > 0)
            {
                tmp = (*env)[i];
                (*env)[i] = (*env)[j];
                (*env)[j] = tmp;
            }
        }
    }
}

static void	export_second(char *arg, t_exe_data *exe)
{
	char	*equal_sign;
	char	*value;
	char	key[256];
	size_t	key_len;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		value = equal_sign + 1;
		if (key_len >= sizeof(key))
		{
			printf("export: variable name too long\n");
			return ;
		}
		ft_memcpy(key, arg, key_len);
		key[key_len] = '\0';
		exe->env = env_set((exe->env), key, value);
	}
	else
		env_set(exe->env, arg, NULL);
	sort_env(exe->env);
	return ;
}

int	builtin_export(char **args, t_exe_data *exe)
{
	int	i;
	int	j;

	i = 0;
	if (!args[1])
	{
		sort_env(exe->env);
		j = -1;
		while ((*exe->env)[++j].key != NULL)
		{
			if ((*exe->env)[j].value)
				printf("declare -x %s=\"%s\"\n", (*exe->env)[j].key,
					(*exe->env)[j].value);
			else
				printf("declare -x %s\n", (*exe->env)[j].key);
		}
		return (0);
	}
	while (args[++i])
		export_second(args[i], exe);
	return (0);
}

int	builtin_unset(char **args, t_exe_data *exe)
{
	int	i;

	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
	{
		env_unset(exe->env, args[i]);
		i++;
	}
	return (0);
}

int	builtin_env(t_exe_data *exe)
{
	int	i;

	i = -1;
	if (!exe || !exe->env || !*exe->env)
		return (1);
	while ((*exe->env)[++i].key != NULL)
		if ((*exe->env)[i].value)
			printf("%s=%s\n", (*exe->env)[i].key, (*exe->env)[i].value);
	return (0);
}

int	builtin_exit(char **args)
{
	g_shell.exit_status = 0;
	if (args[1])
		g_shell.exit_status = ft_atoi(args[1]);
	g_shell.running = 0;
	return (g_shell.exit_status);
}
