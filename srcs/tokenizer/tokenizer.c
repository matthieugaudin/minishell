/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/21 19:18:20 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../includes/errors.h"

void ft_quote_spit(void) {}

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
	else if (node->prev && (node->prev->type == INPUT || node->prev->type == OUTPUT
		|| node->prev->type == APPEND || node->prev->type == HERE_DOC))
		node->type = FILE_T;
	else
		node->type = COMMAND;
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
		return ;
	if (*head == NULL)
		*head = node;
	node->value = line;
	set_token_prev(head, node);
	set_token_type(node);
	node->next = NULL;
}

/*
Check if the line entered has closed quotes in the good sequence.
If not the porgram should stop properly with a syntax error.

'Hello "World"' -> a stirng inside single quotes
"Hello World'" -> a stirng inside double quotes
"Hello World'"" -> the same but after an unclosed quotes
"'"" hello""" -> 3 double quotes
"'"" hello"""' -> 3 double quotes + 1 unclosed
echo "''\"Hello $USER" -> ''"Hello mgaudin -> bash behavior
but as required in the subject we don't have to implement it so just treat
 \" as " so the result is syntax error

*/
void	check_quotes(char *str)
{
	bool	quotes_open;
	char	quote;
	int		i;

	i = 0;
	quotes_open = false;
	while (str[i])
	{
		if (!quotes_open && (str[i] == '\'' || str[i] == '\"'))
		{
			quotes_open = true;
			quote = str[i];
		}
		else if (quotes_open && str[i] == quote)
		{
			quotes_open = false;
		}
		i++;
	}
	if (quotes_open)
	{
		printf("%s", UNCLOSED_QUOTES);
		exit(0);
	}
}

t_token	*tokenizer(char *str)
{
	char	**line;
	t_token	*head;
	int		i;

	head = NULL;
	check_quotes(str);
	line = ft_split(str, ' ');
	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		append_token_node(&head, line[i]);
		i++;
	}
	return (head);
}

/*
TO DO
- ckeck unclosed quotes : OK but to test
- redo ft_split for quotes (do not split spaces between quotes)
- split sticked << and || (if not between quotes)
- convert the linked list ot a cmd structure
- test : e$var == e"cho"
*/