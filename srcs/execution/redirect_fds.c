#include "../../includes/execution.h"

void	redirect_fds(t_data *data, t_cmd *cmd)
{
	if (cmd->fd_in == 0 && cmd->index > 0)
		dup2(data->pipes[cmd->index - 1][0], 0);
	else if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out == 1 && cmd->next)
		dup2(data->pipes[cmd->index][1], 1);
	else if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	// close_pipes(cmd, data->pipes);
}
