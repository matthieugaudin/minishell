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

static void	handle_files(t_token *tokens, t_cmd *cmd)
{
	t_hdoc	*limiter;
	t_file	*file;

	file = NULL;
	limiter = NULL;
	if (tokens->prev->type == HERE_DOC)
	{
		cmd->is_here_doc = true;
		limiter = new_hdoc(tokens->value, tokens->hdoc_quoted);
		add_hdoc_back(&cmd->here_doc, limiter);
	}
	else
	{
		file = new_file(tokens->value, tokens->prev->type);
		add_file_back(&cmd->files, file);
	}
}

static void	set_cmd_content(t_token **tokens, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == FILE_T)
		{
			handle_files(*tokens, cmd);
		}
		else if ((*tokens)->type == COMMAND)
		{
			cmd->args[i] = (*tokens)->value;
			i++;
		}
		*tokens = (*tokens)->next;
	}
}

static void	init_cmd_content(t_cmd *cmd, t_token *tokens)
{
	int	nb_cmds;

	nb_cmds = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			nb_cmds++;
		tokens = tokens->next;
	}
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->fd_out = 1;
	cmd->args = malloc(sizeof(char *) * (nb_cmds + 1));
	cmd->args[nb_cmds] = NULL;
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;

	cmd = NULL;
	cmds = NULL;
	while (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		init_cmd_content(cmd, tokens);
		set_cmd_content(&tokens, cmd);
		set_last_cmd_next(&cmds, cmd);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}
