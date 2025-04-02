#include "../../includes/parser.h"

bool	only_spaces(char *line)
{
	while (*line)
	{
		if (!is_space(*line))
			return (false);
		line++;
	}
	return (true);
}
