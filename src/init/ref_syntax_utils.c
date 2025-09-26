/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:40:12 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 21:32:37 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\b' || c == '\0');
}

int	is_syntax(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	skip_spaces_idx(char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

bool	is_commands(char *line, int i)
{
	if (!line || !line[i])
		return (false);
	i = skip_spaces_idx(line, i);
	if (!line[i] || is_syntax(line[i]))
		return (false);
	return (true);
}
