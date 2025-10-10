/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:03:16 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/10 15:01:34 by mpoirier         ###   ########.fr       */
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

void print_res(char *res)
{
    int i = -1;
    while (res[++i])
    {
        if (res[i] == '\x1D')
            write(1, "(SP)", 4);
        else
            write(1, &res[i], 1);
    }
    write(1, "\n", 1);
}

char	**extract_args(const char *str)
{
	char	*res;
    char	cq;
    bool	quotes;
	int		i;
    int     j;

    printf("raw_args = [%s]\n", str);
    i = -1;
    j = 0;
    res = malloc((ft_strlen(str) * 4 + 1) * sizeof(char));
    quotes = false;
    while (str[++i])
    {
        if (quotes == false && is_quote(str[i]))
        {
            quotes = true;
            cq = str[i];
            res[j++] = '\x1D'; 
        }
        else if (quotes == true && str[i] == cq && (str[i+1] && ft_isspace(str[i+1])))
        {
            quotes = false;
            res[j++] = str[i];
            res[j++] = '\x1D';
            continue ;
        }
        else if (quotes == false && ft_isspace(str[i]))
        {
            res[j++] = '\x1D';
            continue ;
        }
        res[j++] = str[i];
    }
    res[j++] = '\0';
    print_res(res);
    return(ft_split(res, '\x1D'));
}