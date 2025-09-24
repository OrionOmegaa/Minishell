/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:14:09 by mpoirier          #+#    #+#             */
/*   Updated: 2025/08/05 16:14:09 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_value(t_env_data **env, char *key)
{
    int i = -1;
    if (!env || !key)
        return NULL;
    while (env[++i])
    {
        if (env[i] == NULL)
            break;
        if (env[i]->key == NULL)
        {
            i++;
            continue;
        }
        
        if (ft_strncmp(env[i]->key, key, ft_strlen(key)) == 0)
            return (env[i]->value);
    }
    return NULL;
}

int get_var_name_len(char *str)
{
    int len = 0;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
        len++;
    return (len);
}

char *expand_variables(char *input, t_env_data **env)
{
    if (!input)
        return NULL;
    size_t size = ft_strlen(input) * 4 + 1;
    char *res = malloc(size * sizeof(char));
    if (!res)
        return (NULL);
    char *var;
    int i = 0;
    int j = 0;
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1])
        {
            i++;
            if (input[i] == '?')
            {
                var = ft_itoa(g_shell.exit_status);
                if (var)
                {
                    ft_strcpy(res + j, var);
                    j += ft_strlen(var);
                }
                i++;
                continue;
            }
            else if (input[i] == '$')
            {
                var = ft_itoa(getppid());
                if (var)
                    j += ft_strlcpy(res + j, var, ft_strlen(var));
                i++;
                continue;
            }
            int len = get_var_name_len(input + i);
            if (len > 0)
            {
                char var_name[256];
                ft_strlcpy(var_name, input + i, len + 1);
                var = get_env_value(env, var_name);
                if (var)
                    j += ft_strlcpy(res + j, var, ft_strlen(var));
                i += len;
            }
            else
                res[j++] = '$';
        }
        else if (input[i] == '\\' && input[i + 1] == '$')
        {
            res[j++] = '$';
            i += 2;
        }
        else
            res[j++] = input[i++];
    }
    res[j] = '\0';
    return (ft_realloc(res, size, j + 1));
}

void expand_args_array(char **args, t_env_data **env)
{
    if (!args || !env)
        return;
    int i = -1;
    while (args[++i])
    {
        char *expanded = expand_variables(args[i], env);
        if (expanded)
        {
            free(args[i]);
            args[i] = expanded;
        }
    }
}

