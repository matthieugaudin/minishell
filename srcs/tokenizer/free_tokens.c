#include "../../includes/tokenizer.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		free(tokens->value);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
	}
}
