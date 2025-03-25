#include "../../includes/execution.h"

void	create_pipes(t_data *data, t_cmd *cmds)
{
	int	nb_pipes;
	int	i;

	nb_pipes = 0;
	while (cmds->next)
	{
		nb_pipes++;
		cmds = cmds->next;
	}
	data->pipes = malloc(sizeof(int *) * nb_pipes);
	i = 0;
	while (i < nb_pipes)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i]);
		i++;
	}
}
