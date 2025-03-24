#include "../../includes/execution.h"

void	redirect_fds(t_data *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		if (cmds->fd_in == 0 && i > 0)
			dup2(cmds->fd_in, data->pipes[i - 1][0]);
		else if (cmds->fd_in != 0)
			dup2(cmds->fd_in, 0);
		if (cmds->fd_out == 1 && cmds->next)
			dup2(cmds->fd_out, data->pipes[i][1]);
		else if (cmds->fd_out != 1)
			dup2(cmds->fd_out, 1);
		i++;
		cmds = cmds->next;
	}
}
