#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	wait_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;

	while (true)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			// set exit code
		}
		else if (pid == -1)
		{
			// an error occured
		}
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
		// parent
		cmds = cmds->next;
	}
	wait_children(last_pid);
}
