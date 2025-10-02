/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/02 19:41:12 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 1 && av)
		return (ft_printf("Wrong Number Of Argument\nUse : ./Minishell\n"));
	g_shell.env = init_env(envp);
	if (!g_shell.env)
		return (1);
	g_shell.running = 1;
	g_shell.signal_received = 0;
	init_signals();
	minishell(g_shell.env);
	cleanup_shell();
	exit(g_shell.exit_status);
}

/* UTILS */
/* Just didn't have place for it */
/* in the other file ^-^'        */

int	count_args(char *input)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*input)
	{
		if (*input == ' ' || *input == '\t')
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		input++;
	}
	return (count);
}

void	exit_with_error(const char *msg, int code)
{
	perror(msg);
	exit(code);
}
