/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:25:10 by mpoirier          #+#    #+#             */
/*   Updated: 2025/07/16 21:25:10 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir *new_redir(char *file, int append, int here_doc)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->file = ft_strdup(file);
    if (!redir->file)
    {
        free(redir);
        return (NULL);
    }
    redir->append = append;
    redir->here_doc = here_doc;
    return (redir);
}

t_command_data *new_command_data(void)
{
    t_command_data *cmd;

    cmd = malloc(sizeof(t_command_data));
    if (!cmd)
        return (NULL);
    cmd->raw_args = NULL;
    cmd->redir_in = NULL;
    cmd->redir_out = NULL;
    return (cmd);
}

int add_redirection(t_list **redir_list, char *file, int append, int here_doc)
{
    t_redir *redir;
    t_list *node;

    redir = new_redir(file, append, here_doc);
    if (!redir)
        return (-1);
    node = ft_lstnew((void *)redir);
    if (!node)
    {
        free(redir->file);
        free(redir);
        return (-1);
    }
    ft_lstadd_back(redir_list, node);
    return (0);
}

t_command_data *pars_single_command(char *cmd_str)
{
    t_command_data *cmd;
    char *clean_cmd;
    char *token;
    char *current;
    int i;
    int j;

    cmd = new_command_data();
    if (!cmd)
        return (NULL);
    clean_cmd = malloc((ft_strlen(cmd_str) + 1) * sizeof(char));
    if (!clean_cmd)
    {
        free(cmd);
        return (NULL);
    }
    i = 0;
    j = 0;
    current = cmd_str;
    while (current[i])
    {
        if (current[i] == '<')
        {
            i++;
            while (current[i] && (current[i] == ' '))
                i++;
            token = get_next_token(&current[i], &i);
            if (token)
            {
                add_redirection(&cmd->redir_out, token, 1, 0);
                free(token);
            }
            else
            {
                // Redirection simple
                while (current[i] && (current[i] == ' ' || current[i] == '\t'))
                    i++;
                token = get_next_token(&current[i], &i);
                if (token)
                {
                    add_redirection(&cmd->redir_out, token, 0, 0);
                    free(token);
                }
            }
        }
        else
        {
            // Caractère normal, on le copie
            clean_cmd[j++] = current[i++];
        }
    }
    clean_cmd[j] = '\0';
    
    // Extraire les arguments de la commande nettoyée
    cmd->raw_args = extract_args(clean_cmd);
    free(clean_cmd);
    
    if (!cmd->raw_args)
    {
        free_command_data(cmd);
        return (NULL);
    }
    
    return (cmd);
}

char *get_next_token(char *str, int *index)
{
    int start = *index;
    int len = 0;
    char *token;
    bool in_quotes = false;
    char quote_char = 0;
    
    // Ignorer les espaces
    while (str[start] && (str[start] == ' ' || str[start] == '\t'))
        start++;
    
    if (!str[start])
        return (NULL);
    
    *index = start;
    
    // Compter la longueur du token
    while (str[*index] && ((!ft_isspace(str[*index]) && !is_redirect_char(str[*index])) || in_quotes))
    {
        if (is_quote(str[*index]) && !in_quotes)
        {
            in_quotes = true;
            quote_char = str[*index];
        }
        else if (str[*index] == quote_char && in_quotes)
            in_quotes = false;
        (*index)++;
        len++;
    }
    
    if (len == 0)
        return (NULL);
    
    token = malloc(len + 1);
    if (!token)
        return (NULL);
    
    ft_strlcpy(token, &str[start], len + 1);
    return (token);
}
int is_redirect_char(char c)
{
    return (c == '<' || c == '>');
}

char **split_by_pipes(char *line, int *cmd_count)
{
    char **commands;
    int count = 1;
    int i = 0;
    bool in_quotes = false;
    char quote_char = 0;
    
    // Compter le nombre de pipes
    while (line[i])
    {
        if (is_quote(line[i]) && !in_quotes)
        {
            in_quotes = true;
            quote_char = line[i];
        }
        else if (line[i] == quote_char && in_quotes)
            in_quotes = false;
        else if (line[i] == '|' && !in_quotes)
            count++;
        i++;
    }
    
    *cmd_count = count;
    commands = malloc((count + 1) * sizeof(char *));
    if (!commands)
        return (NULL);
    
    // Séparer les commandes
    i = 0;
    int cmd_idx = 0;
    int start = 0;
    in_quotes = false;
    
    while (line[i])
    {
        if (is_quote(line[i]) && !in_quotes)
        {
            in_quotes = true;
            quote_char = line[i];
        }
        else if (line[i] == quote_char && in_quotes)
            in_quotes = false;
        else if (line[i] == '|' && !in_quotes)
        {
            commands[cmd_idx] = ft_substr(line, start, i - start);
            if (!commands[cmd_idx])
            {
                // Libérer en cas d'erreur
                while (cmd_idx > 0)
                    free(commands[--cmd_idx]);
                free(commands);
                return (NULL);
            }
            cmd_idx++;
            start = i + 1;
        }
        i++;
    }
    
    // Dernière commande
    commands[cmd_idx] = ft_substr(line, start, i - start);
    if (!commands[cmd_idx])
    {
        while (cmd_idx > 0)
            free(commands[--cmd_idx]);
        free(commands);
        return (NULL);
    }
    
    commands[count] = NULL;
    return (commands);
}

int parse_command_line(t_pars_data *pars, char *line)
{
    char **cmd_strings;
    int cmd_count;
    int i;
    t_command_data *cmd;
    t_list *node;

    cmd_strings = split_by_pipes(line, &cmd_count);
    if(!cmd_strings)
        return(-1);
    i = -1;
    while ((++i) < cmd_count)
    {
        cmd = pars_single_command(cmd_strings[i]);
        if (!cmd)
        {
            while (i >= 0)
                free(cmd_strings[i--]);
            free(cmd_strings);
            return (-1);
        }
        node = ft_lstnew(cmd);
        if(!node)
        {
            free_command_data(cmd);
            while(i < cmd_count)
                free(cmd_strings[i++]);
            free(cmd_strings);
            return (-1);
        }
        ft_lstadd_back(&pars->commands, node);
        free(cmd_strings[i]);
    }
    free(cmd_strings);
    return (0);
}

void free_redir(void *content)
{
    t_redir *redir;

    redir = (t_redir *)content;
    if (!redir)
        return ;
    if (redir->file)
        free(redir->file);
    free(redir);
}

void free_command_data(void *content)
{
    t_command_data *cmd;
    int i;
    
    cmd = (t_command_data *)content;
    if (!cmd)
        return ;
    if (cmd->raw_args)
    {
        i = 0;
        while (cmd->raw_args[i])
            free(cmd->raw_args[i++]);
        free(cmd->raw_args);
    }
    if (cmd->redir_in)
        ft_lstclear(&cmd->redir_in, free_redir);
    if (cmd->redir_out)
        ft_lstclear(&cmd->redir_out, free_redir);
    free(cmd);
}

void free_pars_data(t_pars_data *pars)
{
    if (!pars)
        return ;
    if (pars->commands)
        ft_lstclear(&pars->commands, free_command_data);
}

t_pars_data *init_pars_data(char *line)
{
    t_pars_data *pars;
    
    if (!line || !*line)
        return (NULL);
    pars = malloc(sizeof(t_pars_data));
    if (!pars)
        return (NULL);
    pars->commands = NULL;
    if (parse_command_line(pars, line) == -1)
    {
        free_pars_data(pars);
        return (NULL);
    }
    return (pars);
}