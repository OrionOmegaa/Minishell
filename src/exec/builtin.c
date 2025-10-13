/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 16:48:53 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_exit(char **args, t_shell *my_shell)
{
	(*my_shell).exit_status = 0;
	if (args[1])
		(*my_shell).exit_status = ft_atoi(args[1]);
	(*my_shell).running = 0;
	return ((*my_shell).exit_status);
}

int	builtin_cd(char **args, t_exe_data *exe, t_shell *my_shell)
{
	char	*path;
	char	cwd[1024];

	if (!args[1])
		path = ft_getenv("HOME", my_shell);
	else
		path = args[1];
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		env_set(exe->env, "PWD", cwd);
	if (!args[1])
		free(path);
	return (0);
}

static void	boucle_echo(char **args, int i)
{
	int	j;

	while (args[++i])
	{
		if (is_quote(args[i][0]))
		{
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] == args[i][0])
					continue ;
				ft_printf("%c", args[i][j]);
			}
		}
		else
			ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
	}
}

int	builtin_echo(char **args)
{
	int		i;
	int		j;
	bool	no_newline;

	i = 0;
	no_newline = false;
	while (args[++i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		no_newline = true;
	}
	i--;
	boucle_echo(args, i);
	if (!no_newline)
		ft_printf("\n");
	return (0);
}

int	exec_builtin(t_cmd_data *cmd, t_exe_data *exe, t_shell *my_shell)
{
	char	*builtin;

	builtin = cmd->args[0];
	if (ft_strncmp(builtin, "echo", INT_MAX) == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strncmp(builtin, "cd", INT_MAX) == 0)
		return (builtin_cd(cmd->args, exe, my_shell));
	else if (ft_strncmp(builtin, "pwd", INT_MAX) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(builtin, "export", INT_MAX) == 0)
		return (builtin_export(cmd->args, exe));
	else if (ft_strncmp(builtin, "unset", INT_MAX) == 0)
		return (builtin_unset(cmd->args, exe));
	else if (ft_strncmp(builtin, "env", INT_MAX) == 0)
		return (builtin_env(exe));
	else if (ft_strncmp(builtin, "exit", INT_MAX) == 0)
		return (builtin_exit(cmd->args, my_shell));
	return (-1);
}
