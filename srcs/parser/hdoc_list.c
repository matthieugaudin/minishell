#include "../../includes/parser.h"

t_hdoc  *new_hdoc(char *limiter, bool is_quoted)
{
	t_hdoc 	*new;

	new = malloc(sizeof(t_hdoc));
	new->limiter = limiter;
	new->expand = is_quoted;
	new->next = NULL;
	return (new);
}

void	add_hdoc_back(t_hdoc **head, t_hdoc *new)
{
	t_hdoc	*last;

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
