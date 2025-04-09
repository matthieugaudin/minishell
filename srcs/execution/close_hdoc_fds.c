#include "../../includes/execution.h"

void	close_hdoc_fds(t_cmd *cmds, bool is_child, int index)
{
	while (cmds)
	{
		if (cmds->fd_in != 0 && (cmds->index != index || !is_child))
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}
