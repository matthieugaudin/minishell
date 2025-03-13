#include "../../includes/minishell.h"

bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	else
		return (false);
}
