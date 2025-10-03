/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:52:47 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/03 15:45:06 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_to_arg_end(const char **str, int *in_quotes, char *quote_char)
{
	while (**str && (!ft_isspace(**str) || *in_quotes))
	{
		if (is_quote(**str) && !*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = **str;
		}
		else if (**str == *quote_char && *in_quotes)
			*in_quotes = 0;
		(*str)++;
	}
}

char	*copy_arg_content(const char *start, int len);

static char	*extract_one_arg(const char **str)
{
	const char	*start;
	int			len;
	int			in_quotes;
	char		quote_char;

	while (**str && ft_isspace(**str))
		(*str)++;
	if (!**str)
		return (NULL);
	start = *str;
	in_quotes = 0;
	quote_char = 0;
	skip_to_arg_end(str, &in_quotes, &quote_char);
	len = *str - start;
	return (copy_arg_content(start, len));
}

char	**extract_args(const char *raw_args)
{
	char		**args;
	const char	*current;
	int			argc;
	int			i;

	if (!raw_args)
		return (NULL);
	argc = pars_count_args(raw_args, 0);
	if (argc == 0)
		return (NULL);
	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	current = raw_args;
	i = -1;
	while ((++i) < argc)
	{
		args[i] = extract_one_arg(&current);
		if (!args[i])
			return (free_args_on_error(args, i));
	}
	args[i] = NULL;
	return (args);
}
