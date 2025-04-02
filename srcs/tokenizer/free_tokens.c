#include "../../includes/tokenizer.h"

void	free_tokens(t_token *tokens, bool alloc_err)
{
	t_token *tmp;

	while (tokens)
	{
		if (tokens->type != COMMAND && tokens->type != FILE_T)
			free(tokens->value);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
	}
	if (alloc_err)
		perror("Memory allocation failed");
}
