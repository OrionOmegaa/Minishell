/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:40:00 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 16:56:51 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* context struct in minishell.h */
void	expand_core(t_expand_ctx *c, t_shell *my_shell);

static char	*expand_variables(char *input, t_env_data **env, t_shell *my_shell)
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
	expand_core(&c, my_shell);
	return (c.res);
}

void	expand_args_array(char **args, t_env_data **env, t_shell *my_shell)
{
	int				i;
	char			*expanded;

	if (!args || !env || !*env)
		return ;
	i = -1;
	while (args[++i])
	{
		expanded = expand_variables(args[i], env, my_shell);
		if (expanded)
		{
			free(args[i]);
			args[i] = expanded;
		}
	}
}

/*util of expand_core*/
bool	need_expand(char *s, int len)
{
	bool	sq;
	bool	dq;
	int		i;

	if (s[len] != '$' || !s[len + 1])
		return (false);
	sq = false;
	dq = false;
	i = -1;
	while ((++i) < len)
	{
		if (s[i] == '\'')
			if (!dq)
				sq = !sq;
		if (s[i] == '"')
			if (!sq)
				dq = !dq;
	}
	return (!sq);
}
