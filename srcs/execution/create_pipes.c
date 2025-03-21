#include "../../includes/execution.h"
#include "../../includes/parser.h"

void	create_pipes(t_data *data)
{
	int	nb_pipes;
	int	i;

	nb_pipes = 1;
	while (data->cmds->next)
	{
		nb_pipes++;
		data->cmds = data->cmds->next;
	}
	data->pipes = malloc(sizeof(int *) * (nb_pipes + 1));
	data->pipes[nb_pipes] = NULL;
	i = 0;
	while (i < nb_pipes)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		pipe(data->pipes[i]);
		i++;
	}
}
