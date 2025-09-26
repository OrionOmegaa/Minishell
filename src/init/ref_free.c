/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:22:25 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 21:22:27 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (redir->file)
		free(redir->file);
	free(redir);
}

void	free_command_data(void *content)
{
	t_command_data	*cmd;
	int				i;

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

void	free_pars_data(t_pars_data *pars)
{
	if (!pars)
		return ;
	if (pars->commands)
		ft_lstclear(&pars->commands, free_command_data);
	free(pars);
}
