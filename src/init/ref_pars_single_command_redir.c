/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_pars_single_command_redir.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:05:31 by mpoirier          #+#    #+#             */
/*   Updated: 2025/09/26 22:05:31 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	psc_grab_filename(char *s, int i, char **tok)
{
	int	start;
	int	len;

	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	start = i;
	len = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t'
		&& s[i] != '<' && s[i] != '>')
	{
		i++;
		len++;
	}
	if (len <= 0)
		return (i);
	*tok = malloc(len + 1);
	if (*tok)
		ft_strlcpy(*tok, &s[start], len + 1);
	return (i);
}

void	psc_assign_redir(t_command_data *cmd, char *tok, int type, int here)
{
	if (!tok)
		return ;
	if (type == 0)
		add_redirection(&cmd->redir_in, tok, 0, here);
	else
		add_redirection(&cmd->redir_out, tok, here, 0);
	free(tok);
}

static int	redir_in(char *s, int i, t_command_data *cmd)
{
	char	*tok;

	tok = NULL;
	if (s[i + 1] == '<')
	{
		i = psc_grab_filename(s, i + 2, &tok);
		psc_assign_redir(cmd, tok, 0, 1);
	}
	else
	{
		i = psc_grab_filename(s, i + 1, &tok);
		psc_assign_redir(cmd, tok, 0, 0);
	}
	return (i);
}

static int	redir_out(char *s, int i, t_command_data *cmd)
{
	char	*tok;

	tok = NULL;
	if (s[i + 1] == '>')
	{
		i = psc_grab_filename(s, i + 2, &tok);
		psc_assign_redir(cmd, tok, 1, 1);
	}
	else
	{
		i = psc_grab_filename(s, i + 1, &tok);
		psc_assign_redir(cmd, tok, 1, 0);
	}
	return (i);
}

int	psc_handle_redir(char *s, int i, t_command_data *cmd)
{
	if (s[i] == '<')
		return (redir_in(s, i, cmd));
	if (s[i] == '>')
		return (redir_out(s, i, cmd));
	return (i);
}
