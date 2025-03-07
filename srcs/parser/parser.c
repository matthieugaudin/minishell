#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

bool	is_redirected(enum e_token type)
{
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HERE_DOC)
		return (true);
	else
		return (false);
}

bool	is_command(t_token *token)
{
	bool	is_cmd;

	is_cmd = false;
	token = token->prev;
	while (token && token->type != PIPE)
	{
		if (token->type == COMMAND)
		{
			is_cmd = true;
			break ;
		}
		token = token->prev;
	}
	return (is_cmd);
}

void    parser(t_token *head)
{
	t_token	*token;

	token = head;
	while (token)
	{
		if (is_redirected(token->type) && (!token->next || token->next != FILE_T))
			return ;
		else if (token->type == PIPE && (!token->prev || !token->next || token->next->type == PIPE))
			return ;
		else if (token->type == PIPE && !is_command(token))
			return ;
		token = token->next;
	}
}
