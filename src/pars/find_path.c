/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:53:44 by mpoirier          #+#    #+#             */
/*   Updated: 2025/06/16 17:53:44 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_path(const char *dir, const char *file)
{
	int		dir_len;
	int		len;
	char	*res;

	dir_len = ft_strlen(dir);
	len = dir_len + ft_strlen(file) + 2;
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, dir, len);
	if (dir_len > 0 && dir[dir_len - 1] != '/')
		ft_strlcat(res, "/", len);
	ft_strlcat(res, file, len);
	return (res);
}

static int	is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

static char	*parsing_second(int dir_len, const char *start, const char *cmd)
{
	char	*dir;
	char	*res;

	dir = malloc((dir_len + 1) * sizeof(char));
	if (dir)
	{
		ft_strlcpy(dir, start, (size_t)(dir_len + 1));
		dir[dir_len] = '\0';
		res = join_path(dir, cmd);
		free(dir);
		if (res)
		{
			if (is_executable(res))
				return (res);
			free(res);
		}
	}
	return (NULL);
}

static char	*parsing_first(const char *start, const char *cmd)
{
	const char	*end;
	int			dir_len;
	char		*full_path;

	while (*start)
	{
		end = ft_strchr(start, ':');
		if (end)
			dir_len = end - start;
		else
			dir_len = ft_strlen(start);
		if (dir_len > 0)
		{
			full_path = parsing_second(dir_len, start, cmd);
			if (full_path)
				return (full_path);
		}
		if (end)
			start = end + 1;
		else
			break ;
	}
	return (NULL);
}

char	*find_path(const char *cmd)
{
	char		*path_env;
	const char	*copy_path;
	char		*full_path;

	if (ft_strchr(cmd, '/'))
		return (NULL);
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	copy_path = path_env;
	full_path = parsing_first((const char *)copy_path, cmd);
	return (full_path);
}
