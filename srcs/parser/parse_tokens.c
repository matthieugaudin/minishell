#include "../../includes/parser.h"

void    parse_tokens(t_token *token)
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
