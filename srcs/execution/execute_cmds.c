#include "../../includes/execution.h"

static void	execute_cmd(t_data *data, t_cmd *cmd)
{
	// check for builtins
	execve(cmd->path, cmd->args, data->env);
}

void	execute_cmds(t_data *data, t_cmd *cmds)
{
	pid_t	pid;
	pid_t	last_pid;

	open_here_doc(cmds, data->env);
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
				set_exec_path(data, cmds);
				redirect_fds(data, cmds);
				execute_cmd(data, cmds);
			}
		}
		cmds = cmds->next;
	}
	wait_children(data, last_pid);
}
