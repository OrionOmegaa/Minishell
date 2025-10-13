/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_pars_single_command_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:45:31 by mpoirier          #+#    #+#             */
/*   Updated: 2025/10/13 13:04:51 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	psc_copy_plain(char *src, char *dst, int i, int *j)
{
	if (src[i] && !is_quote(src[i]) && src[i] != '<' && src[i] != '>')
	{
		dst[(*j)++] = src[i];
		return (i + 1);
	}
	return (i);
}
