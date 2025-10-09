/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:40:00 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/08 17:14:19 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* context struct in minishell.h */

static void	ensure_capacity(struct s_expand_ctx *c, int need)
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

static void	append_str(struct s_expand_ctx *c, char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	ensure_capacity(c, (int)len);
	ft_memcpy(c->res + c->j, s, len);
	c->j += (int)len;
}

static int	expand_special(struct s_expand_ctx *c, t_shell *my_shell)
{
	char	*tmp;

	if (c->input[c->i] == '?')
	{
		tmp = ft_itoa((*my_shell).exit_status);
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

static void	expand_var(struct s_expand_ctx *c)
{
	char	name[256];
	int		len;
	char	*val;
	size_t	vlen;

	len = get_var_name_len(c->input + c->i);
	if (len <= 0)
	{
		c->res[c->j++] = '$';
		return ;
	}
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

void	expand_core(struct s_expand_ctx *c, t_shell *my_shell)
{
	while (c->input[c->i])
	{
		if (c->input[c->i] == '\x01')
			c->i++;
		else if (c->input[c->i] == '\x02')
			c->i++;
		else if (c->input[c->i] == '$' && need_expand(c->input, c->i))
		{
			c->i++;
			if (!expand_special(c, my_shell))
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
	//bluff(&(c->res));
}
