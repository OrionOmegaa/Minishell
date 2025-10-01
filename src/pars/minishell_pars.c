/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 09:40:27 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <termios.h>

void	clear_input_buffer(void)
{
	struct termios	old_termios;
	struct termios	new_termios;
	char			c;

	if (tcgetattr(STDIN_FILENO, &old_termios) != 0)
		return ;
	new_termios = old_termios;
	new_termios.c_cc[VMIN] = 0;
	new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) != 0)
		return ;
	while (read(STDIN_FILENO, &c, 1) > 0)
		;
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

void	handle_line(char *line, t_env_data **env)
{
	t_pars_data	*pars;

	add_history(line);
	pars = init_pars_data(line);
	if (pars)
		executor(env, pars);
	if (pars)
		free_pars_data(pars);
}

// Needs to be tested, did some pretty heavy modifications here. Leo :D
void	minishell(t_env_data **env)
{
	char	*line;

	while (g_shell.running)
	{
		if (g_shell.signal_received == SIGINT)
		{
			g_shell.signal_received = 0;
			continue ;
		}
		else if (g_shell.signal_received == SIGTERM)
			break ;
		line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
			handle_line(line, env);
		free(line);
	}
}
