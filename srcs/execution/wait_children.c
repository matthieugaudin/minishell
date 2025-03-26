#include "../../includes/execution.h"

void	wait_children(t_data *data, pid_t last_pid)
{
	int		status;
	t_cmd	*cmds;

	cmds = data->cmds;
	while (cmds)
	{
		if (wait(&status) == last_pid)
		{
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->status = (128 + WTERMSIG(status));
		}
		cmds = cmds->next;
	}
}
