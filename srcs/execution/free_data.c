#include "../../includes/execution.h"

void	free_data(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;
	int		i;

	while (data->cmds)
	{
		i = 0;
		while (data->cmds->args[i])
		{
			free(data->cmds->args[i]);
			i++;
		}
		free(data->cmds->args);
		data->cmds->args = NULL;
		free(data->cmds->path);
		data->cmds->path = NULL;
		while (data->cmds->files)
		{
			tmp_file = data->cmds->files;
			data->cmds->files = data->cmds->files->next;
			free(tmp_file->name);
			free(tmp_file);
		}
		if (data->cmds->next)
			free(data->pipes[data->cmds->index]);
		tmp_cmd = data->cmds;
		data->cmds = data->cmds->next;
		free(tmp_cmd);
	}
	free(data->pipes);
}
