#ifndef EXECUTION_H
# define EXECUTION_H
# define _GNU_SOURCE

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "parser.h"

extern int g_sigint_flag;

/*==============EXEC==============*/
void	execute_cmds(t_data *data, t_cmd *cmds);
void	open_here_doc(t_data *data, t_cmd *cmds);
void	open_files(t_data *data, t_cmd *cmd, t_file *files);
void	set_exec_path(t_data *data, t_cmd *cmd);
void	redirect_fds(t_data *data, t_cmd *cmds);
void	wait_children(t_data *data, pid_t last_pid);
void	send_error(char *arg, int errno_cpy);
void	create_pipes(t_data *data, t_cmd *cmds);
void	handle_signals(int mode);
void	handle_builtins(t_data *data, t_cmd *cmd);
bool	is_builtin(char *str);
void	handle_signals(int mode);
void	close_pipes(t_cmd *cmds, int **pipes);
int	    s_dup(t_data *data, int fd);
void	s_dup2(t_data *data, int fd, int fd2);
int	    s_fork(t_data *data);
char	*get_file_path(void);
void	expand_line(t_data *data, t_env *env, char **line, int start);
void	expand_digit(t_data *data, char **line, int start);
void	expand_exit(t_data *data, char **line, int start);
void	fill_here_doc(t_data *data, t_file *file, int here_doc);
void	close_hdoc_fds(t_cmd *cmds, bool is_child, int index);
void	handle_builtins(t_data *data, t_cmd *cmd);

#endif /* EXECUTION_H */
