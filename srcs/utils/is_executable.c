#include "../../includes/execution.h"

bool	is_executable(char *arg)
{
	int	i;

	if (arg[0] != '.')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (true);
		i++;
	}
	return (false);
}
