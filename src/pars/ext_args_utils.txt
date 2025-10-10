/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:27:47 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 19:27:47 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

int	is_quote(char c)
{
	return (c == '"' || c == 39);
}

char	**free_args_on_error(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(args[i++]);
	free(args);
	return (NULL);
}

int	pars_count_args(const char *str, int count)
{
	bool	in_word;
	bool	in_quotes;
	char	quote_char;

	in_word = false;
	in_quotes = false;
	while (*str)
	{
		if (is_quote(*str) && !in_quotes)
		{
			in_quotes = true;
			quote_char = *str;
			if (!in_word && ++count)
				in_word = true;
		}
		else if (*str == quote_char && in_quotes)
			in_quotes = false;
		else if (ft_isspace(*str) && !in_quotes)
			in_word = false;
		else if (!in_word && ++count)
			in_word = true;
		str++;
	}
	return (count);
}
