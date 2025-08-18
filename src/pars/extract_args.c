/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:52:47 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/14 18:52:47 by mpoirier         ###   ########.fr       */
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

static int pars_count_args(const char *str, int count)
{
    bool in_word;
    bool in_quotes;
    char quote_char;

    in_word = false;
    in_quotes= false;
    while(*str)
    {
        if(is_quote(*str) && !in_quotes)
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

static void	handle_quote_state(const char *s, bool *in_quotes, char *quote_char, int *i)
{
	if (is_quote(s[*i]) && !*in_quotes)
	{
		*in_quotes = true;
		*quote_char = s[*i];
        /*if (!ft_isspace(s[(*i) + 1]))
            (*i)++;*/
	}
	else if (s[*i]== *quote_char && *in_quotes)
    {
		*in_quotes = false;
        /*if (!ft_isspace(s[(*i) + 1]))
            (*i)++;*/
    }
}

static char	*copy_arg_content(const char *start, int len)
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
		if (!is_quote(start[i]) || (in_quotes && start[i] != quote_char))
			result[j++] = start[i];
		i++;
	}
	result[j] = '\0';
	return (result);
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

static char **free_args_on_error(char **args, int count)
{
    int i;

    i = 0;
    while (i < count)
        free(args[i++]);
    free(args);
    return (NULL);
}

char **extract_args(const char *raw_args)
{
    char **args;
    const char *current;
    int argc;
    int i;

    if (!raw_args)
        return (NULL);
    argc = pars_count_args(raw_args, 0);
    if (argc == 0)
        return (NULL);
    args = malloc((argc + 1) * sizeof(char *) + 1);
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