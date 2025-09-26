/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:40:00 by refactor          #+#    #+#             */
/*   Updated: 2025/09/26 13:24:17 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* context struct in minishell.h */
void	expand_core(t_expand_ctx *c);

char	*expand_variables(char *input, t_env_data **env)
{
	t_expand_ctx	c;

	if (!input)
		return (NULL);
	c.input = input;
	c.env = env;
	c.size = ft_strlen(input) * 4 + 1;
	c.res = malloc(c.size);
	if (!c.res)
		return (NULL);
	c.i = 0;
	c.j = 0;
	expand_core(&c);
	return (c.res);
}

void	expand_args_array(char **args, t_env_data **env)
{
	int				i;
	char			*expanded;

	if (!args || !env || !*env)
		return ;
	i = -1;
	while (args[++i])
	{
		expanded = expand_variables(args[i], env);
		if (expanded)
		{
			free(args[i]);
			args[i] = expanded;
		}
	}
}
