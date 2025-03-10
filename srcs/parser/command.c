#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"

void	set_last_cmd_next(t_cmd **cmds, t_cmd *cmd)
{
	t_token	*last_cmd;

	if (*cmds == NULL)
	{
		*cmds = cmd;
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

/*
    char			**args;
    bool			is_here_doc; // ok
	t_list			*here_doc; // ok
    t_file			*files;
    struct s_cmd	*next; // ok
*/
void	set_cmd_content(t_token **tokens, t_cmd *cmd)
{
	t_list	*limiter;

	limiter = NULL;
	cmd->here_doc = NULL;
	cmd->is_here_doc = false;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == FILE_T)
		{
			if ((*tokens)->prev->type == HERE_DOC)
			{
				cmd->is_here_doc = true;
				limiter = ft_lstnew((*tokens)->next->value);
				ft_lstadd_back(&cmd->here_doc, limiter);
			}
			else if ((*tokens)->prev->type == INPUT)
			{
				// to do
			}
			else if ((*tokens)->prev->type == OUTPUT)
			{
				// to do
			}
			else if ((*tokens)->prev->type == APPEND)
			{
				// to do
			}
		}
		else if ((*tokens)->type == COMMAND)
		{
			// to do
		}
		*tokens = (*tokens)->next;
	}
	cmd->next = NULL;
}

// allocate a cmd node : OK
// set the node values including next : do the function
// points the previous node to this one or points head to the first node : OK
void	append_cmd_node(t_cmd **cmds, t_token **tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	set_cmd_content(tokens, cmd);
	set_last_cmd_next(cmds, cmd);
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (tokens)
	{
		append_cmd_node(&cmd, &tokens);
		tokens++;
	}
	return (cmd);
}
