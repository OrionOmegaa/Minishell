/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:27 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 21:32:37 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_ws(char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	return (s[*i] != 0);
}

static void	upd_quote(char c, bool *in_q, char *q)
{
	if (is_quote(c) && !*in_q)
	{
		*in_q = true;
		*q = c;
	}
	else if (c == *q && *in_q)
		*in_q = false;
}

static int	measure(char *s, int start)
{
	int		i;
	bool	in_q;
	char	q;

	i = start;
	in_q = false;
	q = 0;
	while (s[i] && (!ft_isspace(s[i]) || in_q) && !is_redirect_char(s[i]))
	{
		upd_quote(s[i], &in_q, &q);
		i++;
	}
	return (i - start);
}

char	*get_next_token(char *str, int *index)
{
	int		start;
	int		len;
	char	*token;

	if (!str || !index || *index < 0)
		return (NULL);
	if (!skip_ws(str, index))
		return (NULL);
	start = *index;
	len = measure(str, start);
	if (len <= 0)
		return (NULL);
	*index = start + len;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], len + 1);
	return (token);
}
