/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:03:16 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 17:50:51 by mpoirier         ###   ########.fr       */
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

/*void	print_res(char *res)
{
	int	i;

	i = -1;
	while (res[++i])
	{
		if (res[i] == '\x1D')
			write(1, "(SP)", 4);
		else
			write(1, &res[i], 1);
	}
	write(1, "\n", 1);
}*/
static bool	quote(bool *q, char *cq, char s, char r)
{
	if ((*q) == false && is_quote(s))
	{
		(*q) = true;
		(*cq) = s;
		if (r && r != '\x1D')
			return (true);
	}
	return (false);
}

static void	boucle(int *j, char *res, bool *q, const char *str)
{
	int		i;
	char	cq;

	i = -1;
	cq = 0;
	while (str[++i])
	{
		if ((*j) > 0 && quote(q, &cq, str[i], res[(*j) - 1]))
			res[(*j)++] = '\x1D';
		else if ((*q) == true && str[i] == cq && (str[i + 1]
				&& ft_isspace(str[i + 1])))
		{
			(*q) = false;
			res[(*j)++] = str[i];
			res[(*j)++] = '\x1D';
			continue ;
		}
		else if ((*q) == false && ft_isspace(str[i]))
		{
			if (res[(*j) - 1] && res[(*j) - 1] != '\x1D')
				res[(*j)++] = '\x1D';
			continue ;
		}
		res[(*j)++] = str[i];
	}
}

char	**extract_args(const char *str, char **dest)
{
	char	*res;
	bool	quotes;
	int		j;
	size_t	len;

	j = 0;
	len = (ft_strlen(str) * 4 + 1) * sizeof(char);
	res = malloc(len);
	quotes = false;
	boucle(&j, res, &quotes, str);
	res[j++] = '\0';
	dest = ft_split(res, '\x1D');
	free(res);
	return (dest);
}
