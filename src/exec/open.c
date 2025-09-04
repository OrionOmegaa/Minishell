/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:32 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:49 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_heredoc(char *delimiter)
{
    int pipefd[2];
    char *line;
    
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }
    while ((line = readline("> ")) != NULL)
    {
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    return pipefd[0];
}

int open_outfiles(t_list *redir_out)
{
    //printf("DEBUG: open_outfiles appelé\n");
    int     fd = STDOUT_FILENO;
    int     tmp_fd;
    t_redir *redir;

    if (!redir_out) {
        //printf("DEBUG: Pas de redirection de sortie\n");
        return (STDOUT_FILENO);
    }
    while (redir_out)
    {
        redir = (t_redir *)redir_out->content;
        //printf("DEBUG: redir_out - file='%s', append=%d\n", redir->file, redir->append);
        if (redir->append)
            tmp_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            tmp_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (tmp_fd == -1)
        {
            perror(redir->file);
            if (fd != STDOUT_FILENO)
                close(fd);
            return -1;
        }
        if (fd != STDOUT_FILENO)
            close(fd);
        fd = tmp_fd;
        //printf("DEBUG: open('%s') retourne fd=%d\n", redir->file, fd);
        redir_out = redir_out->next;
    }
    return fd;
}

int open_infiles(t_list *redir_in)
{
    //printf("DEBUG: open_infiles appelé\n");
    int fd = STDIN_FILENO;
    int tmp_fd;
    t_redir *redir;

    if (!redir_in)
        return STDIN_FILENO;

    while (redir_in)
    {
        redir = (t_redir *)redir_in->content;
        //printf("DEBUG: redir_in - file='%s', here_doc=%d\n", redir->file, redir->here_doc);
        if (redir->here_doc)
            tmp_fd = handle_heredoc(redir->file);
        else {
            tmp_fd = open(redir->file, O_RDONLY);
            //printf("DEBUG: open('%s') = %d\n", redir->file, fd);
        }
        if (tmp_fd == -1)
        {
            perror(redir->file);
            if (fd != STDIN_FILENO)
                close(fd);
            return -1;
        }
        if (fd != STDIN_FILENO)
            close(fd);
        fd = tmp_fd;
        redir_in = redir_in->next;
    }
    return fd;
}
