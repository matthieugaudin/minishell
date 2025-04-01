#include "../../includes/execution.h"

static void	execute_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	(void)data;
	// check for builtins
	// convert envp to char **
	execve(cmd->path, cmd->args, envp);
}

void	close_hdoc_fds(t_cmd *cmds, bool is_child, int index)
{
	while (cmds)
	{
		if (cmds->fd_in != 0 && (cmds->index != index || !is_child))
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}

void	execute_cmds(t_data *data, t_cmd *cmds, char **envp)
{
	pid_t	pid;
	pid_t	last_pid;

	open_here_doc(cmds, data->env);
	while (cmds && sigint_flag != 1)
	{
		pid = fork();
		handle_signals(2);
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
		{
			close_hdoc_fds(data->cmds, true, cmds->index);
			open_files(cmds, cmds->files);
			if (cmds->args[0] != NULL)
			{
				set_exec_path(data, cmds);
				redirect_fds(data, cmds);
				execute_cmd(data, cmds, envp);
			}
		}
		if (cmds->index > 0)
			close(data->pipes[cmds->index - 1][0]);
		if (cmds->next)
			close(data->pipes[cmds->index][1]);
		cmds = cmds->next;
	}
	close_hdoc_fds(data->cmds, false, 0);
	wait_children(data, last_pid);
}
