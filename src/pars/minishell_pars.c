/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 16:58:50 by mpoirier         ###   ########.fr       */
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

static void	handle_line(char *line, t_shell *my_shell)
{
	t_pars_data	*pars;

	add_history(line);
	pars = init_pars_data(line, my_shell);
	if (pars)
		executor(my_shell, pars);
	if (pars)
		free_pars_data(pars);
}

void	minishell(t_shell *my_shell)
{
	char	*line;

	while ((*my_shell).running)
	{
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			continue ;
		}
		else if (g_sig == SIGTERM)
			break ;
		line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
			handle_line(line, my_shell);
		free(line);
	}
}

/* UTILS */

char	*ft_getenv(const char *var, t_shell *my_shell)
{
	int			i;
	char		*res;
	t_env_data	tmp;

	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa((*my_shell).exit_status));
	if (!ft_strncmp(var, "0", 2))
		return (ft_strdup("HEY(!)SHELL 🪜"));
	i = 0;
	tmp = (*(*my_shell).env)[i];
	while (tmp.key != NULL)
	{
		if (!ft_strncmp(tmp.key, var, INT_MAX))
		{
			res = ft_strdup(tmp.value);
			return (res);
		}
		tmp = (*(*my_shell).env)[++i];
	}
	return (NULL);
}
