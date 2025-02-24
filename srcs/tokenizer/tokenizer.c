/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/24 21:29:12 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../includes/errors.h"

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
If not, the porgram stop properly with a syntax error message.
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

/*
Tokenize the line entered by the user. It verifies the unclosed quotes, create well-splitted tokens that will
be send to the parser, and regroup each command in a struct.
*/
t_token	*tokenizer(char *line)
{
	char	**tokens;
	t_token	*head;
	int		i;

	head = NULL;
	check_quotes(line);
	tokens = split_tokens(line);
	i = 0;
	while (tokens[i])
	{
		append_token_node(&head, tokens[i]);
		i++;
	}
	return (head);
}

/*
TO DO
	-> check for unclosed quotes
	-> split the line into a t_token linked list
	-> give to every line a token
	-> convert the tokens into t_cmd structure
*/
