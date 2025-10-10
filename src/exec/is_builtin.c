/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:51:36 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/09 13:55:01 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", INT_MAX) == 0)
		return (1);
	return (0);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", INT_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", INT_MAX) == 0)
		return (1);
	return (0);
}
