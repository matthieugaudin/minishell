#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"

void	set_last_cmd_next(t_cmd *head, t_cmd *node)
{
	while (head->next)
	{
		head = head->next;
	}
	head->next = node;
}

void	set_cmd_content(t_token **tokens, t_cmd *cmd)
{
	while (*tokens && (*tokens)->type != PIPE)
	{
		*tokens = (*tokens)->next;
	}
}

void	append_cmd_node(t_cmd **cmds, t_token **tokens)
{
	// allocate a cmd node : OK
	// set the last cmds to the cmd allocated
	// set all cmd values by iterating through tokens by adresss

	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (*cmds == NULL)
		*cmds = cmd;
	set_last_cmd_next(*cmds, cmd);
	set_cmd_content(tokens, cmd);
	cmd->pipe = 0;
	cmd->next = NULL;
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_token	*token;
	t_cmd	*cmd;

	token = tokenizer("<infile cat -e > outfile|grep $USER");
	expansion(token, envp);
	cmd = create_cmd(token);
}
