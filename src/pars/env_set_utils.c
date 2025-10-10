/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:24:43 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 19:24:43 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_known(t_env_data **env, char *key)
{
	int	i;

	i = -1;
	while ((*env)[++i].key != NULL)
	{
		if (ft_strncmp((*env)[i].key, key, INT_MAX) == 0
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
