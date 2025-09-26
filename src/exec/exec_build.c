/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refactor <refactor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:00 by refactor          #+#    #+#             */
/*   Updated: 2025/09/26 17:30:00 by refactor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**duplicate_args(char **src)
{
	int		cnt;
	char	**dst;
	int		i;

	if (!src)
		return (NULL);
	cnt = 0;
	while (src[cnt])
		cnt++;
	dst = malloc(sizeof(char *) * (cnt + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < cnt)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			return (free(dst), NULL);
		}
	}
	dst[cnt] = NULL;
	return (dst);
}

static t_cmd_data	*build_cmd_node(t_command_data *cur, int fd_in, int fd_out)
{
	char		**args;
	char		*path;
	t_cmd_data	*node;

	args = duplicate_args(cur->raw_args);
	if (!args)
		return (NULL);
	expand_args_array(args, g_shell.env);
	path = find_path(args[0]);
	if (!path)
		path = ft_strdup(args[0]);
	node = cmd_new(args, path, fd_in, fd_out);
	return (node);
}

void	open_files(t_command_data *cur, int *fd_in, int *fd_out, int *skip)
{
	*fd_in = open_infiles(cur->redir_in);
	if (*fd_in == -1)
		*skip = 1;
	*fd_out = open_outfiles(cur->redir_out);
	if (*fd_out == -1)
		*skip = 1;
}

t_cmd_data	*interpreter(t_pars_data *pars)
{
	t_list			*lst;
	t_command_data	*cur;
	t_cmd_data		*cmds;
	t_cmd_data		*node;
	int				fds_and_skip[3];

	cmds = NULL;
	lst = pars->commands;
	while (lst)
	{
		cur = (t_command_data *)lst->content;
		fds_and_skip[2] = 0;
		open_files(cur, &fds_and_skip[0], &fds_and_skip[1], &fds_and_skip[2]);
		if (!fds_and_skip[2])
		{
			node = build_cmd_node(cur, fds_and_skip[0], fds_and_skip[1]);
			if (node)
				cmd_add_back(&cmds, node);
		}
		lst = lst->next;
	}
	return (cmds);
}
