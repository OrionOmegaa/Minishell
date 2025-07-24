/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/07/18 15:16:39 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_env_data *env;
    if (ac != 1 && av)
        return (ft_printf("Wrong Number Of Argument\nUse : ./Minishell\n"));
    env = init_env(envp);
    minishell(&env);
    free_env_data(env);
    return 0;
}
