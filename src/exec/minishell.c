/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/09/21 22:15:58 by mpoirier         ###   ########.fr       */
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
