char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, 100) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

void    exec(char *cmd, char **env)
{
    char    **s_cmd;
    char    *path;

    s_cmd = ft_split(cmd, ' ');
    path = get_path(s_cmd[0], env);
    if (execve(path, s_cmd, env) == -1)
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(s_cmd[0], 2);
        ft_free_tab(s_cmd);
        exit(0);
    }
}

void    exec_pipe(char *cmd, char **env)
{
    pid_t	pid;
    int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

///////////////////////////////////////////////////////////

char *find_command_path(char *cmd)
{
    char    buffer[4096];
    char    *res;
    char    *path;
    char    *start;
    int     i;
    int     len;
    int     j;
    int     k;
    int     m;

    i = 0;
    if (!cmd)
        return NULL;

    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return cmd;
        return NULL;
    }
    path = getenv("PATH");
    if (!path)
        return NULL;
    while (*path)
    {
        start = path;
        while (*path && *path != ':')
            path++;
        len = path - start;
        i = 0;
        while (i < len && i < 4096 - 1)
        {
            buffer[i] = start[i];
            i++;
        }
        buffer[i] = '\0';
        j = 0;
        while (buffer[j]) j++;
        buffer[j++] = '/';
        k = 0;
        while (cmd[k] && j < 4096 - 1)
            buffer[j++] = cmd[k++];
        buffer[j] = '\0';
        if (access(buffer, X_OK) == 0)
        {
            res = malloc(j + 1);
            m = 0;
            while (m <= j)
            {
                res[m] = buffer[m];
                m++;
            }
            return res;
        }
        if (*path == ':')
            path++;
    }
    return NULL;
}

void execute_command(char *input, char **env)
{
    char    **args;
    pid_t   pid;
    char    *cmd_path;
    int     status;

    args = split_args(input);
    pid = fork();
    if (!args || !args[0])
        return;
    if (ft_strncmp(args[0], "exit", 5) == 0 || ft_strncmp(args[0], "Exit", 5) == 0)
    {
        free_args(args);
        exit(0);
    }
    if (pid == 0)
    {
        cmd_path = find_command_path(args[0]);
        if (!cmd_path)
        {
            write(2, "Command Not Found\n", 19);
            exit(127);
        }
        execve(cmd_path, args, env);
        perror("Execve");
        exit(1);
    } 
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
        perror("Fork");
    free_args(args);
}