/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/18 15:44:26 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void minishell(t_env_data **env)
{
    char *line;
    t_pars_data *pars;

    while (1)
    {
        pars = NULL;
        line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
        if (!line)
            break;
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
        clear_input_buffer();
    }
}