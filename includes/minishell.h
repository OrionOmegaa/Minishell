/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:53:37 by hdescamp          #+#    #+#             */
/*   Updated: 2025/05/16 14:56:49 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes

# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "libft/libft.h"
# define _GNU_SOURCE
# define MAX_ARGS 42

//Utils

int     count_args(char *input);
void    free_args(char **args);

//Exec

void    execute_command(char *input, char **env);
char    *find_command_path(char *cmd);

//Parse

char    **split_args(char *input);

#endif