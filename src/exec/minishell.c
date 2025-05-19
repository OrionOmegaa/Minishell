/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
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
        execute_command(line, env);
        free(line);
    }
}

int main(int ac, char **av, char **env)
{
    if (ac != 1 && av)
        return (printf("Wrong Number Of Argument\nUse : ./Minishell\n"));
    minishell(env);
    return 0;
}
