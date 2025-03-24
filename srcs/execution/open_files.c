#include "../../includes/execution.h"

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
