/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:29:20 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/22 19:09:58 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shell g_shell = {NULL, 1, 0, 0};

void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.signal_received = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
		g_shell.signal_received = SIGTERM;
}

void init_signals(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	cleanup_shell(void)
{
	int i;
	
	if (!g_shell.env)
		return;
	
	i = 0;
	while (g_shell.env[i])
	{
		if (g_shell.env[i]->key)
		{
			free(g_shell.env[i]->key);
			g_shell.env[i]->key = NULL;
		}
		if (g_shell.env[i]->value)
		{
			free(g_shell.env[i]->value);
			g_shell.env[i]->key = NULL;
		}
		free(g_shell.env[i]);
		g_shell.env[i] = NULL;
		i++;
	}
	free(g_shell.env);
	g_shell.env = NULL;
	/*if (g_shell.env)
	{
		i = -1;
		while (g_shell.env[++i]->key != NULL)
		{
			free(g_shell.env[i]->key);
			free(g_shell.env[i]->value);
		}
		free(g_shell.env);
		g_shell.env = NULL;
	}*/
}
