/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:14:02 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/29 20:14:02 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Version avec debugging pour identifier le problème
int builtin_export(char **args, t_exe_data *exe)
{
    int i = 1;

    if (!args[1])
    {
        printf("DEBUG: Affichage de l'environnement\n");
        int j = 0;
        while (exe->env[j].key != NULL)
        {
            if (exe->env[j].value)
                ft_printf("declare -x %s=\"%s\"\n", exe->env[j].key, exe->env[j].value);
            else
                ft_printf("declare -x %s\n", exe->env[j].key);
            j++;
        }
        return 0;
    }

    while (args[i])
    {
        printf("DEBUG: Traitement de l'argument: '%s'\n", args[i]);
        char *equal_sign = ft_strchr(args[i], '=');
        if (equal_sign)
        {
            size_t key_len = equal_sign - args[i];
            char key[256];
            char *value = equal_sign + 1;

            if (key_len >= sizeof(key))
            {
                ft_printf("export: variable name too long\n");
                i++;
                continue;
            }

            // Copier la clé
            memcpy(key, args[i], key_len);
            key[key_len] = '\0';

            printf("DEBUG: Clé extraite: '%s', Valeur: '%s'\n", key, value);
            
            // Appeler env_set
            printf("DEBUG: Appel de env_set avec key='%s', value='%s'\n", key, value);
            env_set(&(exe->env), key, value);
            printf("DEBUG: Retour de env_set\n");
            
            // Vérifier si la variable a été ajoutée
            int j = 0;
            int found = 0;
            while (exe->env[j].key != NULL)
            {
                if (strcmp(exe->env[j].key, key) == 0)
                {
                    printf("DEBUG: Variable trouvée! %s=%s\n", exe->env[j].key, exe->env[j].value);
                    found = 1;
                    break;
                }
                j++;
            }
            if (!found)
                printf("DEBUG: ERREUR - Variable non trouvée après env_set!\n");
        }
        else
        {
            printf("DEBUG: Variable sans valeur: '%s'\n", args[i]);
            env_set(&(exe->env), args[i], NULL);
        }
        i++;
    }
    return 0;
}

// Version debug de env_set
void env_set(t_env_data **env, char *key, char *value)
{
    int i;
    int len;

    printf("DEBUG env_set: Entrée avec key='%s', value='%s'\n", key, value ? value : "(null)");

    if (!*env)
    {
        printf("DEBUG env_set: Initialisation de l'environnement\n");
        *env = malloc(sizeof(t_env_data));
        if (!*env)
        {
            printf("DEBUG env_set: ERREUR - malloc failed\n");
            return ;
        }
        (*env)[0].key = NULL;
        (*env)[0].value = NULL;
    }
    
    if (!key)
    {
        printf("DEBUG env_set: ERREUR - key est NULL\n");
        return ;
    }

    // Chercher si la variable existe déjà
    i = is_known(env, key);
    printf("DEBUG env_set: is_known retourne %d\n", i);
    
    if (i != -1)
    {
        printf("DEBUG env_set: Variable existante, mise à jour\n");
        free((*env)[i].value);
        (*env)[i].value = value ? ft_strdup(value) : NULL;
        printf("DEBUG env_set: Valeur mise à jour\n");
        return ;
    }

    // Nouvelle variable
    printf("DEBUG env_set: Nouvelle variable\n");
    len = env_len(*env);
    printf("DEBUG env_set: Taille actuelle de l'env: %d\n", len);
    
    *env = ft_realloc(*env, len * sizeof(t_env_data), 
        (len + 2) * sizeof(t_env_data)); // +2 pour la nouvelle variable + terminateur
    if (!*env)
    {
        printf("DEBUG env_set: ERREUR - ft_realloc failed\n");
        return ;
    }
    
    printf("DEBUG env_set: Realloc réussi\n");
    
    // Ajouter la nouvelle variable
    (*env)[len].key = ft_strdup(key);
    (*env)[len].value = value ? ft_strdup(value) : NULL;
    (*env)[len + 1].key = NULL;
    (*env)[len + 1].value = NULL;
    
    printf("DEBUG env_set: Variable ajoutée à l'index %d\n", len);
}