/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:52:47 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 22:33:14 by mpoirier         ###   ########.fr       */
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

/*// Uncommented 2 blocks, don't know if that was the thing to do
static void	handle_quote_state(const char *s, bool *in_quotes, char *quote_char,
		int *i)
{
	if (is_quote(s[*i]) && !*in_quotes)
	{
		*in_quotes = true;
		*quote_char = s[*i];
		if (!ft_isspace(s[(*i) + 1]))
			(*i)++;
	}
	else if (s[*i] == *quote_char && *in_quotes)
	{
		*in_quotes = false;
		if (!ft_isspace(s[(*i) + 1]))
			(*i)++;
	}
}*/

/*static char	*copy_arg_content(const char *start, int len)
{
	char	*result;
	int		i;
	int		j;
	bool	in_quotes;
	char	quote_char;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = false;
	while (i < len)
	{
		handle_quote_state(start, &in_quotes, &quote_char, &i);
		//added
		if (start[i] == '$' && i + 1 < len && is_quote(start[i + 1]))
		{
			i++;
			continue;
		}
		if (!is_quote(start[i]) || (in_quotes && start[i] != quote_char))
			result[j++] = start[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}*/

static void process_char(const char *start, int len, char *result, 
                         int *i, int *j, bool *in_sq, bool *in_dq)
{
    if (start[*i] == '\'' && !(*in_dq))
    {
        *in_sq = !(*in_sq);
        (*i)++;
        if (!(*in_sq))
            result[(*j)++] = '\x02';
        return;
    }
    if (start[*i] == '"' && !(*in_sq))
    {
        *in_dq = !(*in_dq);
        (*i)++;
        if (!(*in_dq))
            result[(*j)++] = '\x02';
        return;
    }
    if (start[*i] == '$' && *in_sq)
    {
        result[(*j)++] = '\x01';
        (*i)++;
        return;
    }
    if (start[*i] == '$' && !(*in_sq) && !(*in_dq) &&
        *i + 1 < len && 
        (start[*i + 1] == '"' || start[*i + 1] == '\''))
    {
        (*i)++;
        return;
    }
    result[(*j)++] = start[(*i)++];
}

static char	*copy_arg_content(const char *start, int len)
{
	char	*res;
	int		i;
	int		j;
	bool	in_sq;
	bool	in_dq;
	
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	in_sq = false;
	in_dq = false;
	while (i < len)
		process_char(start, len, res, &i, &j, &in_sq, &in_dq);
	res[j] = '\0';
	return (res);
}

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
	printf("raw_args = [%s]\n", raw_args);
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
		printf("args[%d] = [%s]\n", i, args[i]);
	}
	args[i] = NULL;
	return (args);
}
