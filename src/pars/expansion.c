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
    printf("DEBUG get_env_value: recherche key='%s'\n", key);
    if (!env || !key) {
        printf("DEBUG get_env_value: env ou key NULL\n");
        return NULL;
    }
    while (env[++i])
    {
        printf("DEBUG: env[%d] = %p\n", i, env[i]);
        if (env[i] == NULL) {
            printf("DEBUG: env[%d] est NULL, arrêt\n", i);
            break;
        }
        printf("DEBUG: env[%d]->key = %p\n", i, env[i]->key);
        if (env[i]->key == NULL) {
            printf("DEBUG: env[%d]->key est NULL, passer au suivant\n", i);
            i++;
            continue;
        }
        printf("DEBUG: env[%d]->key='%s'\n", i, env[i]->key);
        
        if (ft_strncmp(env[i]->key, key, ft_strlen(key)) == 0) {
            printf("DEBUG get_env_value: TROUVÉ! value='%s'\n", env[i]->value);
            return (env[i]->value);
        }
        if (i > 100) {
            printf("DEBUG get_env_value: BOUCLE INFINIE DÉTECTÉE\n");
            break;
        }
    }
    printf("DEBUG get_env_value: variable '%s' non trouvée\n", key);
    return NULL;
}

int get_var_name_len(char *str)
{
    int len = 0;

    //printf("DEBUG get_var_name_len: str='%s'\n", str);
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_')) {
        //printf("DEBUG get_var_name_len: retourne 0 (premier char invalide)\n");
        return (0);
    }
    while (str[len] && (ft_isalnum(str[len]) || str[len] == '_')) { 
        //printf("DEBUG get_var_name_len: char[%d]='%c' (ASCII=%d)\n", len, str[len], (int)str[len]);
        len++;
        if (len > 50) {
            //printf("DEBUG get_var_name_len: BOUCLE INFINIE DÉTECTÉE\n");
            break;
        }
    }
    //printf("DEBUG get_var_name_len: retourne len=%d\n", len);
    return (len);
}

char *expand_variables(char *input, t_env_data **env)
{
    if (!input)
        return NULL;
    //printf("DEBUG EXPAND: input='%s' (len=%zu)\n", input, strlen(input));
    size_t size = ft_strlen(input) * 4 + 1;
    //printf("DEBUG EXPAND: buffer alloué = %zu bytes\n", size);
    char *res = malloc(size * sizeof(char));
    if (!res)
        return (NULL);
    char *var;
    int i = 0;
    int j = 0;
    while (input[i])
    {
        //printf("DEBUG LOOP: i=%d, char='%c'\n", i, input[i]);
        if (input[i] == '$' && input[i + 1])
        {
            //printf("DEBUG: $ détecté à position %d\n", i);
            i++;
            if (input[i] == '?')
            {
                var = ft_itoa(g_shell.exit_status);
                if (var)
                {
                    ft_strcpy(res + j, var);
                    j += ft_strlen(var);
                    //free(var);
                }
                i++;
                continue;
            }
            else if (input[i] == '$')
            {
                var = ft_itoa(getppid());
                if (var)
                {
                    j += ft_strlcpy(res + j, var, ft_strlen(var));
                    //free(var);
                }
                i++;
                continue;
            }
            int len = get_var_name_len(input + i);
            if (len > 0)
            {
                char var_name[256];
                ft_strlcpy(var_name, input + i, len + 1);
                //printf("DEBUG: Recherche variable '%s'\n", var_name);
                var = get_env_value(env, var_name);
                printf("DEBUG: get_env_value retourne %p\n", var);
                if (var) {
                    printf("DEBUG: j=%d, var='%s' (len=%zu)\n", j, var, strlen(var));
                    printf("DEBUG: Espace restant dans buffer = %zu\n", size - j);
                    j += ft_strlcpy(res + j, var, ft_strlen(var));
                    printf("DEBUG: j après copie = %d\n", j);
                }
                else
                    printf("DEBUG: Variable '%s' non trouvée\n", var_name);
                //free(var);
                printf("DEBUG: Avant i += len, i=%d, len=%d\n", i, len);
                i += len;
                printf("DEBUG: Après i += len, i=%d\n", i);
            }
            else {
                //printf("DEBUG: Pas de variable valide, copie $ et avance\n");
                res[j++] = '$';
            }
        }
        else if (input[i] == '\\' && input[i + 1] == '$')
        {
            res[j++] = '$';
            i += 2;
        }
        else {
            //printf("DEBUG: Copie char normal '%c'\n", input[i]);
            res[j++] = input[i++];
        }
        if (i > 100) {
            printf("DEBUG: BOUCLE INFINIE DÉTECTÉE, ARRÊT FORCÉ\n");
            break;
        }
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

