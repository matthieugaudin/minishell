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
				exit_code(WEXITSTATUS(status), true);
			else if (WIFSIGNALED(status))
				exit_code(128 + WTERMSIG(status), true);
		}
		cmds = cmds->next;
	}
}
