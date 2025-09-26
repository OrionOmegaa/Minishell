/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_pars_single_command_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:45:31 by abonnard          #+#    #+#             */
/*   Updated: 2025/09/26 21:48:25 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	psc_copy_plain(char *src, char *dst, int i, int *j)
{
	if (src[i] && src[i] != '<' && src[i] != '>')
	{
		dst[*j] = src[i];
		(*j)++;
		return (i + 1);
	}
	return (i);
}
