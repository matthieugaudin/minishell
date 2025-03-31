#include "../../includes/tokenizer.h"

int	exit_code(int new_code, bool to_set)
{
	static int	code;

	if (to_set)
		code = new_code;
	return (code);
}
