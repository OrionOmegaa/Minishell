/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_syntax_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:55:02 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/06 16:43:25 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_redir_pair(char a, char b)
{
	printf("bash: syntax error near unexpected token `%c", a);
	printf("%c' \n", b);
}

static void	pipe_err(int dbl, t_shell *my_shell)
{
	if (dbl)
		printf("bash: syntax error near unexpected token `||'\n");
	else
		printf("bash: syntax error near unexpected token `|'\n");
	(*my_shell).exit_status = 2;
}

static int	check_body(char *trim, t_shell *my_shell)
{
	int	i;

	i = 0;
	while (trim[i])
	{
		if (trim[i] == '|' && !is_commands(trim, i + 1))
		{
			if (trim[i + 1] == '|' && !is_commands(trim, i + 2))
				pipe_err(1);
			else if (!is_commands(trim, i + 2))
				pipe_err(0);
			if ((*my_shell).exit_status == 2)
				return (1);
		}
		i++;
	}
	return (0);
}

int	final_syntax_check(char *trim, int len, t_shell *my_shell)
{
	if (check_body(trim, (*)))
		return (1);
	if (len > 0)
		return (0);
	return (0);
}
