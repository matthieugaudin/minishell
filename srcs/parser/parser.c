#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

bool	is_redir(enum e_token type)
{
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HERE_DOC)
		return (true);
	else
		return (false);
}

void    parser(t_token *token)
{
	t_token	*first_token;

	first_token = token;
	while (token)
	{
		if (is_redir(token->type) && (!token->next || token->next->type != FILE_T))
			syntax_error(first_token, token->value[0]);
		if (token->type == PIPE && (!token->prev || !token->next || token->next->type == PIPE))
			syntax_error(first_token, '|');
		token = token->next;
	}
}
