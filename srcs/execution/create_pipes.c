#include "../../includes/execution.h"

static void	close_failure(t_cmd *cmds, int **pipes, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		close(pipes[cmds->index][0]);
		close(pipes[cmds->index][1]);
		cmds = cmds->next;
		i++;
	}
}

static void	free_data_pipe(t_data *data, int j)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 0;
	while (data->cmds)
	{
		if (data->cmds->fd_in != 0)
			close(data->cmds->fd_in);
		if (data->cmds->fd_out != 1)
			close(data->cmds->fd_out);
		free_cmd_content(data->cmds);
		if (data->cmds->next && i <= j)
			free(data->pipes[data->cmds->index]);
		tmp_cmd = data->cmds;
		data->cmds = data->cmds->next;
		free(tmp_cmd);
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
}


static void	pipe_failure(t_data *data, int i)
{
	close_failure(data->cmds, data->pipes, i);
	// free_all(data, -2);

	free(data->line);
	data->line = NULL;
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_data_pipe(data, i);

	free_env_exp(&data->env, &data->exp);
	free(data);
	data = NULL;
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	create_pipes(t_data *data, t_cmd *cmds)
{
	int	nb_pipes;
	int	i;

	nb_pipes = 0;
	while (cmds && cmds->next)
	{
		nb_pipes++;
		cmds = cmds->next;
	}
	data->pipes = malloc(sizeof(int *) * nb_pipes);
	if (!data->pipes)
		free_all(data, EXIT_FAILURE);
	i = 0;
	while (i < nb_pipes)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			free_all(data, EXIT_FAILURE);
		if (pipe(data->pipes[i]) == -1)
			pipe_failure(data, i);
		i++;
	}
}
