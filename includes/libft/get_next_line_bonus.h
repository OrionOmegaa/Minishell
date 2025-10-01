/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:46:27 by mpoirier          #+#    #+#             */
/*   Updated: 2025/01/08 10:55:32 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ftt_strjoin(char *s1, char *s2);
char	*ftt_strchr(const char *string, int searched_char );
void	ftt_bzero(void *s, size_t n);
void	*ftt_calloc(size_t element_count, size_t element_size);
size_t	ftt_strlen(const char *str);

#endif
