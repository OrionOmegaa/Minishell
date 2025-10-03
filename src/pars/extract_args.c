/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:52:47 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/03 16:25:56 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_to_arg_end(const char **str, bool *in_quotes, char *quote_char)
{
	if (is_quote(**str))
	{
		*in_quotes = true;
		*quote_char = (**str);
		(*str)++;
	}
	while (**str)
	{
		if (is_quote(**str))
		{
			if (*in_quotes && *quote_char == **str)
				*in_quotes = !(*in_quotes);
			else if (!(*in_quotes)) 
			{
				*quote_char = **str;
				*in_quotes = !(*in_quotes);
			}
		}
		else if (!(*in_quotes) && ft_isspace(**str))
			break;
		(*str)++;
	}
}

char	*copy_arg_content(const char *start, int len);

static char	*extract_one_arg(const char **str)
{
	const char	*start;
	int			len;
	bool		in_quotes;
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
