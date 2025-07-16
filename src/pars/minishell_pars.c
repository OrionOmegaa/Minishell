/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/16 21:50:01 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    minishell(t_env_data **env)
{
    char    *line;
    t_pars_data *pars;

    while (1)
    {
        line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
        if (!line)
            break;
        if (*line) {
            add_history(line);
            pars = init_pars_data(line);
            if (pars)
            {
                executor(env, pars);
                free_pars_data(pars);
            }
        }
        free(line);
    }
}