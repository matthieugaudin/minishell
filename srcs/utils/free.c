/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:42 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:43 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	free_cmd_content(t_cmd *cmd)
{
	int		i;
	t_file	*tmp_file;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	cmd->args = NULL;
	free(cmd->path);
	cmd->path = NULL;
	while (cmd->files)
	{
		tmp_file = cmd->files;
		cmd->files = cmd->files->next;
		free(tmp_file->name);
		free(tmp_file);
	}
}

void	free_data(t_data *data)
{
	t_cmd	*tmp_cmd;

	while (data->cmds)
	{
		if (data->cmds->fd_in != 0)
			close(data->cmds->fd_in);
		if (data->cmds->fd_out != 1)
			close(data->cmds->fd_out);
		free_cmd_content(data->cmds);
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
