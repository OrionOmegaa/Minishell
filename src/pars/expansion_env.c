/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:40:00 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/08 17:38:43 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env_data **env, char *key)
{
	int		i;

	if (!env || !*env || !key)
		return (NULL);
	i = -1;
	while ((*env)[++i].key)
		if (!ft_strncmp((*env)[i].key, key, ft_strlen(key))
			&& ft_strlen((*env)[i].key) == ft_strlen(key))
			return ((*env)[i].value);
	return (NULL);
}

int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[len] && str[len] != '\x02'
		&& (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
