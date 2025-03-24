#include "../../includes/tokenizer.h"

bool	is_quotes(t_token *node)
{
	int	i;

	i = 0;
	while (node->value[i])
	{
		if (node->value[i] == '\'' || node->value[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}
