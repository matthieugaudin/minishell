#include "../../includes/execution.h"

void	close_pipes(t_cmd *cmds, int **pipes)
{
	while (cmds && cmds->next)
	{
		close(pipes[cmds->index][0]);
		close(pipes[cmds->index][1]);
		cmds = cmds->next;
	}
}

void	redirect_fds(t_data *data, t_cmd *cmd)
{
	if (cmd->fd_in == 0 && cmd->index > 0)
		dup2(data->pipes[cmd->index - 1][0], 0);
	else if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out == 1 && cmd->next)
		dup2(data->pipes[cmd->index][1], 1);
	else if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	close_pipes(data->cmds, data->pipes);
}
