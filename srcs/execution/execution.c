#include "../../includes/execution.h"
#include "../../includes/parser.h"

void	wait_children(t_data *data, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
			 	data->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->status = (128 + WTERMSIG(status));
		}
		pid = wait(&status);
	}
}

/*
when an open fails the command is not executed
do i quit directly or i use /dev/null and i go to the next command
*/
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
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
		{
			perror("open");
			//free
			// exit
		}
	}
	cmd->files = cmd->files->next;
}

void	execute_cmd(t_data *data, t_cmd *cmd)
{
	execve(cmd->path, cmd->args, data->env);
}

void	execution(t_data *data, t_cmd *cmds)
{
	pid_t	pid;
	pid_t	last_pid;

	// open_here_doc(cmds);
	while (cmds)
	{
		pid = fork();
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
		{
			open_files(cmds);
			if (cmds != NULL)
			{
				check_builtins(cmds);
				find_exec_path(cmds);
				redirect_fds(cmds);
				execute_cmd(data, cmds);
			}
		}
		// parent
		cmds = cmds->next;
	}
	wait_children(data, last_pid);
}
