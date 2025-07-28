/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:29:20 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/28 15:16:07 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shell g_shell = {NULL, 1, 0};

void cleanup_and_exit(int sig)
{
    (void)sig;
    cleanup_shell();
    write(1, "\n", 1);
    exit(0);
}

void init_signals(void)
{
	signal(SIGINT, cleanup_and_exit);
	signal(SIGTERM, cleanup_and_exit);
	signal(SIGQUIT, cleanup_and_exit);
}

void	cleanup_shell(void)
{
	int i;
	if (g_shell.env)
	{
		i = -1;
		while (g_shell.env[++i].key != NULL)
		{
			free(g_shell.env[i].key);
			free(g_shell.env[i].value);
		}
		free(g_shell.env);
		g_shell.env = NULL;
	}
}
