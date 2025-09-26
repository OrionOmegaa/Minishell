/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:34 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 21:23:37 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*wrap_node(t_redir *r)
{
	return (ft_lstnew((void *)r));
}

t_redir	*new_redir(char *file, int append, int here_doc)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	redir->append = append;
	redir->here_doc = here_doc;
	return (redir);
}

t_command_data	*new_command_data(void)
{
	t_command_data	*cmd;

	cmd = malloc(sizeof(t_command_data));
	if (!cmd)
		return (NULL);
	cmd->raw_args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	return (cmd);
}

static int	push_redir(t_list **list, t_redir *r)
{
	t_list	*node;

	node = wrap_node(r);
	if (!node)
	{
		free(r->file);
		free(r);
		return (-1);
	}
	ft_lstadd_back(list, node);
	return (0);
}

int	add_redirection(t_list **redir_list, char *file, int append, int here_doc)
{
	t_redir	*redir;

	redir = new_redir(file, append, here_doc);
	if (!redir)
		return (-1);
	if (push_redir(redir_list, redir) == -1)
		return (-1);
	return (0);
}
