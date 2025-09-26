/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:14:09 by mpoirier          #+#    #+#             */
/*   Updated: 2025/08/05 16:14:09 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env_data **env, char *key)
{
	int	i;

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
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static void	ensure_capacity(t_expand_ctx *c, int need)
{
	char	*tmp;
	size_t	new_size;

	if ((size_t)(c->j + need + 1) <= c->size)
		return ;
	new_size = (c->j + need + 1) * 2;
	tmp = ft_realloc(c->res, c->size, new_size);
	if (!tmp)
		return ;
	c->res = tmp;
	c->size = new_size;
}

static void	append_str(t_expand_ctx *c, const char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	ensure_capacity(c, (int)len);
	ft_memcpy(c->res + c->j, s, len);
	c->j += (int)len;
}

static int	expand_special(t_expand_ctx *c)
{
	char	*tmp;

	if (c->input[c->i] == '?')
	{
		tmp = ft_itoa(g_shell.exit_status);
		append_str(c, tmp);
		free(tmp);
		c->i++;
		return (1);
	}
	if (c->input[c->i] == '$')
	{
		tmp = ft_itoa(getppid());
		append_str(c, tmp);
		free(tmp);
		c->i++;
		return (1);
	}
	return (0);
}

static void	expand_var(t_expand_ctx *c)
{
	char	name[256];
	int		len;
	char	*val;
	size_t	vlen;

	len = get_var_name_len(c->input + c->i);
	if (len <= 0)
		return ((void)(c->res[c->j++] = '$'));
	if ((size_t)len >= sizeof(name))
		len = (int) sizeof(name) - 1;
	ft_memcpy(name, c->input + c->i, (size_t)len);
	name[len] = '\0';
	val = get_env_value(c->env, name);
	if (val)
	{
		vlen = ft_strlen(val);
		ensure_capacity(c, (int)vlen);
		ft_memcpy(c->res + c->j, val, vlen);
		c->j += (int)vlen;
	}
	c->i += len;
}

static void	expand_core(t_expand_ctx *c)
{
	while (c->input[c->i])
	{
		if (c->input[c->i] == '$' && c->input[c->i + 1])
		{
			c->i++;
			if (!expand_special(c))
				expand_var(c);
		}
		else if (c->input[c->i] == '\\' && c->input[c->i + 1] == '$')
		{
			c->res[c->j++] = '$';
			c->i += 2;
		}
		else
			c->res[c->j++] = c->input[c->i++];
	}
	c->res[c->j] = '\0';
}

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
	int		i;
	char	*expanded;

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
