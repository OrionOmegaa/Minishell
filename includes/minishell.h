/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:53:37 by hdescamp          #+#    #+#             */
/*   Updated: 2025/10/01 18:26:14 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pwd.h>
# include <readline/history.h>
# include <readline/readline.h>
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
# define _GNU_SOURCE
# define MAX_ARGS 42

// Struct Pars

typedef struct s_pars_data
{
	t_list					*commands;
}							t_pars_data;

typedef struct s_command_data
{
	char					**raw_args;
	t_list					*redir_in;
	t_list					*redir_out;
}							t_command_data;

typedef struct s_cmd_data
{
	char					**args;
	char					*path;
	int						fd_in;
	int						fd_out;
	int						skip_cmd;
	pid_t					pid;
	struct s_cmd_data		*next;
}							t_cmd_data;

typedef struct s_env_data
{
	char					*key;
	char					*value;
}							t_env_data;

typedef struct s_shell
{
	t_env_data				**env;
	int						running;
	int						exit_status;
	volatile sig_atomic_t	signal_received;
}							t_shell;

extern t_shell				g_shell;

// Struct Exec
typedef struct s_redir
{
	char					*file;
	int						append;
	int						here_doc;
}							t_redir;

typedef struct s_exec_data
{
}							t_exec_data;

typedef struct s_exe_data
{
	t_pars_data				*pars;
	t_env_data				**env;
	char					**envp;
	int						prev_pipe;
	t_cmd_data				*cmds;
}							t_exe_data;

/* ********************** EXPANSION CONTEXT STRUCT *********************** */
typedef struct s_expand_ctx
{
	char					*input;
	t_env_data				**env;
	char					*res;
	size_t					size;
	int						i;
	int						j;
}							t_expand_ctx;

/* ******************************* UTILITIES ****************************** */
void						exit_with_error(const char *msg, int code);
int							count_args(char *input);
int							free_exe(t_exe_data *exe, int ret_val,
								int free_envp, char *err_msg);

/* ***************************** EXECUTION API ***************************** */
t_exe_data					init_exe(t_env_data **env, t_pars_data *pars);
void						ft_free_tab(char **tab);
void						exec(char *cmd, char **env);
int							open_infiles(t_list *redir_in);
int							open_outfiles(t_list *redir_out);
int							is_builtin(const char *cmd);
int							exec_builtin(t_cmd_data *cmd, t_exe_data *exe);
t_cmd_data					*cmd_new(char **args, char *path, int fd_in,
								int fd_out);
void						cmd_add_back(t_cmd_data **lst, t_cmd_data *new);
t_env_data					**init_env(char **env);
int							executor(t_env_data **env, t_pars_data *pars);
void						free_cmd(t_cmd_data *cmd);
/* exec split components */
t_cmd_data					*interpreter(t_pars_data *pars);
void						child_process(t_exe_data *exe, t_cmd_data *cmd,
								int fds[2]);
void						parent_process(t_exe_data *exe, t_cmd_data *cmd,
								int fds[2]);
void						last_status(t_cmd_data *cur);
void						free_cmd_list(t_cmd_data *lst);
void						execute_pipeline(t_exe_data *exe,
								t_pars_data *pars);
bool						execute_single_builtin(t_exe_data *exe,
								t_cmd_data *cmds);
bool						execute_single_exit(t_cmd_data *cmds);
bool						prepare_fds(t_cmd_data *cur, int fds[2]);

/* ******************************** BUILTINS ******************************* */
int							builtin_cd(char **args, t_exe_data *exe);
int							builtin_pwd(void);
int							builtin_export(char **args, t_exe_data *exe);
int							builtin_unset(char **args, t_exe_data *exe);
int							builtin_env(t_exe_data *exe);
int							builtin_exit(char **args);

/* ******************************* PARSER API ****************************** */
void						minishell(t_env_data **env);
int							find_fd(char *file, int in_or_out);
char						**extract_args(const char *raw_args);
t_env_data					**env_set(t_env_data **env, char *key, char *value);
t_env_data					**env_unset(t_env_data **env, char *key);
char						*find_path(const char *cmd);
int							ft_isspace(char c);
int							is_syntax(char c);
int							is_quote(char c);

/* ********************* PARSER LOW LEVEL HELPERS ************************* */
t_redir						*new_redir(char *file, int append, int here_doc);
t_command_data				*new_command_data(void);
int							add_redirection(t_list **redir_list, char *file,
								int append, int here_doc);
t_command_data				*pars_single_command(char *cmd_str);
char						*get_next_token(char *str, int *index);
int							is_redirect_char(char c);
char						**split_by_pipes(char *line, int *cmd_count);
int							parse_command_line(t_pars_data *pars, char *line);
void						free_redir(void *content);
void						free_command_data(void *content);
void						free_pars_data(t_pars_data *pars);
t_pars_data					*init_pars_data(char *line);

/* ******************************* MISC HELPERS **************************** */
void						init_signals(void);
void						handle_signal(int sig);
void						free_env_data(t_env_data *env);
void						cleanup_shell(void);
int							env_len(t_env_data *env);
int							is_known(t_env_data **env, char *key);
int							is_env_builtin(const char *cmd);
void						expand_args_array(char **args, t_env_data **env);
char						*expand_variables(char *input, t_env_data **env);
int							get_var_name_len(char *str);
char						*get_env_value(t_env_data **env, char *key);
int							cmd_count(t_list *lst);
int							check_syntax_errors(char *line);
int							count_segments(char *line);
int							iterate_segments(char *line, char **cmds);
void						update_quote(char c, bool *in_q, char *q);
int							iterate_segments_body(char *line, char **cmds);
int						final_syntax_check(char *trim, int len);
void					print_redir_pair(char a, char b);
bool					is_commands(char *line, int i);
#endif
