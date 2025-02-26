/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:00:37 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

static void	set_token_type(t_token *node)
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
}

static void	set_token_prev(t_token **head, t_token *node)
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

static void	append_token_node(t_token **head, char *line)
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
Tokenize the line entered by the user. It verifies the unclosed quotes,
create well-splitted tokens that will be send to the parser,
and regroup each command in a struct.
*/
t_token	*tokenizer(char *line)
{
	char	**tokens;
	t_token	*head;
	int		i;

	head = NULL;
	check_quotes(line);
	check_line(line, "<>|&");
	tokens = split_tokens(line);
	i = 0;
	while (tokens[i])
	{
		append_token_node(&head, tokens[i]);
		i++;
	}
	return (head);
}
