#ifndef EXECUTION_H
# define EXECUTION_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "parser.h"

typedef struct s_data
{
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmds;
	int		**pipes;
}	t_data;

/*==============EXEC==============*/
void	execute_cmds(t_data *data, t_cmd *cmds, char **envp);
void    open_here_doc(t_cmd *cmds, t_env *env);
void	open_files(t_cmd *cmd, t_file *files);
void	set_exec_path(t_data *data, t_cmd *cmd);
void	redirect_fds(t_data *data, t_cmd *cmds);
void	wait_children(t_data *data, pid_t last_pid);
void	send_error(char *arg, int errno_cpy);
void	create_pipes(t_data *data, t_cmd *cmds);
void	free_data(t_data *data);

#endif /* EXECUTION_H */