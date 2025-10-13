/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:29:20 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 16:59:46 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
		g_sig = SIGTERM;
}

void	init_signals(void)
{
	rl_catch_signals = 1;
	rl_catch_sigwinch = 1;
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	cleanup_shell(t_shell *my_shell)
{
	t_env_data	*arr;
	int			i;

	if (!(*my_shell).env || !(*my_shell).env[0])
		return ;
	arr = (*my_shell).env[0];
	i = -1;
	while (arr[++i].key != NULL)
	{
		if (arr[i].key)
			free(arr[i].key);
		if (arr[i].value)
			free(arr[i].value);
	}
	free(arr);
	free((*my_shell).env);
	(*my_shell).env = NULL;
}
