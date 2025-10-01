/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:38 by abonnard          #+#    #+#             */
/*   Updated: 2025/10/01 18:40:13 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	edge_pipe(char *trim, int len)
{
	if (trim[0] == '|')
	{
		if (trim[1] == '|')
			printf("bash: syntax error near unexpected token `||'\n");
		else
			printf("bash: syntax error near unexpected token `|'\n");
		g_shell.exit_status = 2;
		return (1);
	}
	if (len > 0 && trim[len - 1] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		g_shell.exit_status = 2;
		return (1);
	}
	return (0);
}

static void	redir_pair_or_single(char *t, int pair)
{
	if (pair)
		print_redir_pair(t[0], t[1]);
	else
		printf("bash: syntax error near unexpected token `%c' \n", t[0]);
}

static int	redir_edge(char *t, int len)
{
	if (t[0] == '>' || t[0] == '<')
	{
		if ((len - 2) < 1)
			printf("bash: syntax error near unexpected token `newline'\n");
		else
			redir_pair_or_single(t, (t[1] == '>' || t[1] == '<'));
		g_shell.exit_status = 2;
		return (1);
	}
	if (len > 1 && (t[len - 1] == '>' || t[len - 1] == '<'))
	{
		redir_pair_or_single(t, (t[len - 2] == '>' || t[len - 2] == '<'));
		g_shell.exit_status = 2;
		return (1);
	}
	return (0);
}

int	check_syntax_errors(char *line)
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
	if (edge_pipe(trim, len)
		|| redir_edge(trim, len)
		|| final_syntax_check(trim, len))
		return (free(trim), 1);
	free(trim);
	return (0);
}
