#include "../../includes/builtins.h"

void	free_data(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;
	int		i;

	while (data->cmds)
	{
		i = 0;
		if (data->cmds->fd_in != 0)
			close(data->cmds->fd_in);
		if (data->cmds->fd_out != 1)
			close(data->cmds->fd_out);
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
	data->pipes = NULL;
}

void	free_list(t_env **list)
{
	t_env	*current;
	t_env	*next;

	if (list && *list)
	{
		current = *list;
		while (current)
		{
			next = current->next;
			free_env_node(current);
			current = next;
		}
		*list = NULL;
	}
}

void	free_env_exp(t_env **env, t_env **exp)
{
	free_list(env);
	free_list(exp);
}

void	free_all(t_data *data, int status)
{
	if (status != -2)
	{
		close_pipes(data->cmds, data->pipes);
		free_env_exp(&data->env, &data->exp);
	}
	free(data->line);
	data->line = NULL;
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_data(data);
	if (status != -2)
	{
		free(data);
		data = NULL;
		rl_clear_history();
		exit(status);
	}
}
