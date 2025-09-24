/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_data *cmd_new(char **args, char *path, int fd_in, int fd_out)
{
    t_cmd_data *new;

    new = malloc(sizeof(t_cmd_data));
    if (!new)
        return (NULL);
    new->args = args;
    new->path = path;
    new->fd_in = fd_in;
    new->fd_out = fd_out;
    new->skip_cmd = 0;
    new->pid = -1;
    new->next = NULL;
    return (new);
}

int cmd_count(t_list *lst)
{
    int count = 0;
    t_list *tmp = lst;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}

void cmd_add_back(t_cmd_data **lst, t_cmd_data *new)
{
    t_cmd_data *tmp;

    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}