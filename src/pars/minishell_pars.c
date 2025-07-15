/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/14 17:08:58 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    minishell(char **env)
{
    char    *line;

    while (1)
    {
        line = readline("\001\033[1;36m\002Minishell> \001\033[0m\002");
        if (!line)
            break;
        if (*line)
            add_history(line);
        executor(env, line);
        free(line);
    }
}