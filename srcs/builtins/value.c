#include "../../includes/builtins.h"

int	value(t_data *data, int status, bool to_exit)
{
	if (to_exit)
	{
		free_all(data, status);
		return (1);
	}
	else
	{
		exit_code(status, true);
		return (0);
	}
}
