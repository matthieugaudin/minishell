#include "../../includes/parser.h"

bool	is_last_redir(t_file *file)
{
	bool			redir_in;

	redir_in = false;
	if (file->type == HERE_DOC || file->type == INPUT)
		redir_in = true;
	file = file->next;
	while (file)
	{
		if ((redir_in && (file->type == HERE_DOC || file->type == INPUT))
			|| (!redir_in && (file->type == OUTPUT || file->type == APPEND)))
			return (false);
		file = file->next;
	}
	return (true);
}
