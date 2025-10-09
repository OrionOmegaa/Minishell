/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:38 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/07 19:07:43 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	edge_pipe(char *trim, int len, t_shell *my_shell)
{
	if (trim[0] == '|')
	{
		if (trim[1] == '|')
			printf("bash: syntax error near unexpected token `||'\n");
		else
			printf("bash: syntax error near unexpected token `|'\n");
		(*my_shell).exit_status = 2;
		return (1);
	}
	if (len > 0 && trim[len - 1] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		(*my_shell).exit_status = 2;
		return (1);
	}
	return (0);
}

static void	redir_pair_or_single(char *t, int pair, char c, int i)
{
	if (pair)
		print_redir_pair(t[i], t[i + 1]);
	else
		printf("bash: syntax error near unexpected token `%c' \n", c);
}

static int	redir_edge(char *t, int len, t_shell *my_shell)
{
	int	f;

	f = len - 2;
	if (t[0] == '>' || t[0] == '<')
	{
		if ((f) < 1)
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			redir_pair_or_single(t, (t[1] == '>' || t[1] == '<'), t[0], 0);
		(*my_shell).exit_status = 2;
		return (1);
	}
	if (len > 1 && (t[f + 1] == '>' || t[f + 1] == '<'))
	{
		redir_pair_or_single(t, (t[f] == '>' || t[f] == '<'), t[f + 1], f);
		(*my_shell).exit_status = 2;
		return (1);
	}
	return (0);
}

static int	second_quote(char *s, t_shell *my_shell)
{
	int		i;
	bool	sq;
	bool	dq;

	i = -1;
	sq = false;
	dq = false;
	while (s[++i])
	{
		if (s[i] == '"')
			dq = !dq;
		if (s[i] == '\'')
			sq = !sq;
	}
	if (s[i - 1] == '\\')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		(*my_shell).exit_status = 2;
	}
	if (sq || dq)
	{
		printf("bash: second quote not found\n");
		(*my_shell).exit_status = 2;
	}
	return ((sq || dq || s[i - 1] == '\\'));
}

int	check_syntax_errors(char *line, t_shell *my_shell)
{
	char	*trim;
	int		len;

	if (!line)
		return (0);
	trim = ft_strtrim(line, " \t");
	if (!trim)
		return (0);
	len = ft_strlen(trim);
	if (!len)
		return (free(trim), 0);
	if (edge_pipe(trim, len, my_shell)
		|| redir_edge(trim, len, my_shell)
		|| final_syntax_check(trim, len, my_shell)
		|| second_quote(trim, my_shell))
		return (free(trim), 1);
	free(trim);
	return (0);
}
