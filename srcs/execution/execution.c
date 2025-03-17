#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/*
wait(&status) returns the pid of the finished process
(on error  || if finish) -1 is returned and errno is setup
errno == ECHILD if finished
if the last cmd is running and a signal happend, the exit code is different
exemple : ctrl C during a sleep 
*/
void	wait_children(void) {}

void	open_files(t_cmd *cmd)
{
	while (cmd->files)
	{
		if (cmd->files->type == INPUT)
			cmd->fd_in = open(cmd->files->name, O_RDONLY);
		else if (cmd->files->type == OUTPUT)
			cmd->fd_out = open(cmd->files->name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (cmd->files->type == APPEND)
			cmd->fd_out = open(cmd->files->name, O_RDWR | O_CREAT | O_APPEND, 0664);
		if (cmd->fd_out == -1)
			cmd->fd_out = open("/dev/null", O_RDONLY);
	}
	cmd->files = cmd->files->next;
}

void	check_builtins(t_cmd *cmd)
{
	char *cmd_name;

	cmd_name = cmd->args[0];
	if (ft_strcmp(cmd_name, "cd"));
		// to do
	else if (ft_strcmp(cmd_name, "echo"));
		// to do
}

void	execution(t_cmd *cmds)
{
	pid_t	pid;
	pid_t	last_pid;
	
	open_here_doc(cmds);
	while (cmds)
	{
		pid = fork();
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
		{
			open_files(cmds);
			check_builtins(cmds);
			find_exec_path(cmds);
			redirect_fds(cmds);
			execute_cmd(cmds);
		}
		else
		{
			// parent
		}
		cmds = cmds->next;
	}
	wait_children();
}
