/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/28 16:15:27 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <termios.h>

void clear_input_buffer(void)
{
    struct termios old_termios;
    struct termios new_termios;
    char c;
    
    // Sauvegarde les attributs actuels du terminal
    if (tcgetattr(STDIN_FILENO, &old_termios) != 0)
        return;
    
    // Copie les attributs et modifie pour lecture non-bloquante
    new_termios = old_termios;
    new_termios.c_cc[VMIN] = 0;   // Lecture non-bloquante
    new_termios.c_cc[VTIME] = 0;  // Pas de timeout
    
    // Applique les nouveaux attributs
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) != 0)
        return;
    
    // Lit tous les caractères disponibles
    while (read(STDIN_FILENO, &c, 1) > 0)
        ;
    
    // Restaure les attributs originaux
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

/* ORIGNAL
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}*/

void	minishell(t_env_data **env)
{
	char		*line;
	t_pars_data	*pars;

	while (g_shell.running)
	{
        pars = NULL;
		line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
		if (!line)
		{
			g_shell.running = 0;
			break ;
		}
		if (*line) 
        {
            add_history(line);
            pars = init_pars_data(line);
            if (pars)
                executor(env, pars);
        }
        if (pars)
        {
            free_pars_data(pars);
            pars = NULL;
        }
		free(line);
		//clear_input_buffer();
    }
}