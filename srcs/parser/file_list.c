#include "../../includes/parser.h"

t_file	*new_file(char *name, enum e_token type)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	new->name = name;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_file_back(t_file **head, t_file *new)
{
	t_file	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}
