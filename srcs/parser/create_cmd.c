#include "../../includes/parser.h"

static void	set_last_cmd_next(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*last_cmd;

	if (*cmds == NULL)
	{
		*cmds = cmd;
		return ;
	}
	else
	{
		last_cmd = *cmds;
		while (last_cmd->next)
		{
			last_cmd = last_cmd->next;
		}
		last_cmd->next = cmd;
	}
}

static void	handle_files(t_data *data, t_token *tokens, t_cmd *cmd)
{
	t_file	*file;

	if (tokens->prev->type == HERE_DOC)
		cmd->is_here_doc = true;
	file = new_file(data, tokens->value, tokens->prev->type, tokens->hdoc_quoted);
	add_file_back(&cmd->files, file);
}

static void	set_cmd_content(t_data *data, t_token **tokens, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == FILE_T)
		{
			handle_files(data, *tokens, cmd);
		}
		else if ((*tokens)->type == COMMAND)
		{
			cmd->args[i] = (*tokens)->value;
			i++;
		}
		*tokens = (*tokens)->next;
	}
}

static void	init_cmd_content(t_data *data, t_cmd *cmd, t_token *tokens, int index)
{
	int			nb_cmds;

	nb_cmds = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			nb_cmds++;
		tokens = tokens->next;
	}
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->fd_out = 1;
	cmd->index = index;
	cmd->args = malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmd->args)
	{
		free(cmd);
		free_all(data, EXIT_FAILURE);
	}
	cmd->args[nb_cmds] = NULL;
}

t_cmd	*create_cmd(t_data *data, t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;
	int		index;

	cmd = NULL;
	cmds = NULL;
	index = 0;
	while (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			free_all(data, EXIT_FAILURE);
		init_cmd_content(data, cmd, tokens, index);
		set_cmd_content(data, &tokens, cmd);
		set_last_cmd_next(&cmds, cmd);
		if (tokens)
			tokens = tokens->next;
		index++;
	}
	return (cmds);
}
