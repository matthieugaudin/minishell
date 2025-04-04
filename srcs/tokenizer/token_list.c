#include "../../includes/tokenizer.h"

void	set_token_type(t_token *node)
{
	if (ft_strcmp(node->value, "<") == 0)
		node->type = INPUT;
	else if (ft_strcmp(node->value, ">") == 0)
		node->type = OUTPUT;
	else if (ft_strcmp(node->value, "<<") == 0)
		node->type = HERE_DOC;
	else if (ft_strcmp(node->value, ">>") == 0)
		node->type = APPEND;
	else if (ft_strcmp(node->value, "|") == 0)
		node->type = PIPE;
	else if (node->prev && (node->prev->type == INPUT
			|| node->prev->type == OUTPUT || node->prev->type == APPEND
			|| node->prev->type == HERE_DOC))
		node->type = FILE_T;
	else
		node->type = COMMAND;
	if (node->prev && node->prev->type == HERE_DOC && is_quotes(node))
		node->hdoc_quoted = true;
	else
		node->hdoc_quoted = false;
}

void	set_token_prev(t_token **head, t_token *node)
{
	t_token	*last_node;

	if (*head == node)
	{
		node->prev = NULL;
	}
	else
	{
		last_node = *head;
		while (last_node->next)
		{
			last_node = last_node->next;
		}
		last_node->next = node;
		node->prev = last_node;
	}
}

void	append_token_node(t_token **head, char *line)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
	{
		free(line);
		free_tokens(*head, true);
		exit(1);
	}
	if (*head == NULL)
		*head = node;
	node->value = line;
	set_token_prev(head, node);
	set_token_type(node);
	node->next = NULL;
}
