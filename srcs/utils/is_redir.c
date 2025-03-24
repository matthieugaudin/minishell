#include "../../includes/tokenizer.h"

bool	is_redir(enum e_token type)
{
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HERE_DOC)
		return (true);
	else
		return (false);
}
