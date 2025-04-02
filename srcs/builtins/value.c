#include "../../includes/builtins.h"

int	value(int status, bool to_exit)
{
	if (to_exit)
	{
		// free
		exit(status);
	}
	else
		return (status);
}
