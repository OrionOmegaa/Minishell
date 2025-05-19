/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:57:29 by mpoirier          #+#    #+#             */
/*   Updated: 2025/05/16 14:57:30 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **split_args(char *input)
{
    int     argc;
    char    **args;
    int     i;
    int     j;

    argc = count_args(input);
    args = malloc(sizeof(char *) * (argc + 1));
    i = 0;
    j = 0;
    while (*input && i < argc)
    {
        while (*input == ' ' || *input == '\t')
            input++;
        char *start = input;
        while (*input && *input != ' ' && *input != '\t')
            input++;
        int len = input - start;
        args[i] = malloc(len + 1);
        while (j < len)
        {
            args[i][j] = start[j];
            j++;
        }
        args[i][len] = '\0';
        i++;
    }
    args[i] = NULL;
    return args;
}