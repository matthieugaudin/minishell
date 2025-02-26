/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 11:22:36 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../includes/errors.h"

// static void	set_token_type(t_token *node)
// {
// 	if (ft_strcmp(node->value, "<") == 0)
// 		node->type = INPUT;
// 	else if (ft_strcmp(node->value, ">") == 0)
// 		node->type = OUTPUT;
// 	else if (ft_strcmp(node->value, "<<") == 0)
// 		node->type = HERE_DOC;
// 	else if (ft_strcmp(node->value, ">>") == 0)
// 		node->type = APPEND;
// 	else if (ft_strcmp(node->value, "|") == 0)
// 		node->type = PIPE;
// 	else if (node->prev && (node->prev->type == INPUT || node->prev->type == OUTPUT
// 		|| node->prev->type == APPEND || node->prev->type == HERE_DOC))
// 		node->type = FILE_T;
// 	else
// 		node->type = COMMAND;
// }

// static void	set_token_prev(t_token **head, t_token *node)
// {
// 	t_token	*last_node;
// 	if (*head == node)
// 	{
// 		node->prev = NULL;
// 	}
// 	else
// 	{
// 		last_node = *head;
// 		while (last_node->next)
// 		{
// 			last_node = last_node->next;
// 		}
// 		last_node->next = node;
// 		node->prev = last_node;
// 	}
// }

// static void	append_token_node(t_token **head, char *line)
// {
// 	t_token	*node;
// 	node = malloc(sizeof(t_token));
// 	if (!node)
// 		return ;
// 	if (*head == NULL)
// 		*head = node;
// 	node->value = line;
// 	set_token_prev(head, node);
// 	set_token_type(node);
// 	node->next = NULL;
// }

// /*
// Check if the line entered has closed quotes in the good sequence.
// */
// void	check_quotes(char *str)
// {
// 	bool	quotes_open;
// 	char	quote;
// 	int		i;
// 	i = 0;
// 	quotes_open = false;
// 	while (str[i])
// 	{
// 		if (!quotes_open && (str[i] == '\'' || str[i] == '\"'))
// 		{
// 			quotes_open = true;
// 			quote = str[i];
// 		}
// 		else if (quotes_open && str[i] == quote)
// 		{
// 			quotes_open = false;
// 		}
// 		i++;
// 	}
// 	if (quotes_open)
// 	{
// 		printf("%s", UNCLOSED_QUOTES);
// 		exit(0);
// 	}
// }


bool	in_quotes(char *str, int j)
{
	bool	quotes_open;
	char	quote;
	int		i;
	
	i = 0;
	quotes_open = false;
	while (i <= j)
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
	return (quotes_open);
}

bool	check_line(char *str, char *set)
{
	int	i;
	int	nb_car;
	
	while (*set)
	{
		i = 0;
		nb_car = 0;
		while (str[i])
		{
			if (!in_quotes(str, i) && str[i] == *set)
				nb_car++;
			else if (!in_quotes(str, i) && nb_car > 0 && str[i] != *set)
				nb_car = 0;
			if (((*set == '<' || *set == '>') && nb_car > 2) ||
				(*set == '|' && nb_car > 1) || (*set == '&' && nb_car > 0))
				return (false);
			i++;
		}
		set++;
	}
	return (true);
}

/*
Tokenize the line entered by the user. It verifies the unclosed quotes, create well-splitted tokens that will
be send to the parser, and regroup each command in a struct.
*/
// t_token	*tokenizer(char *line)
// {
// 	char	**line;
// 	t_token	*head;
// 	int		i;

// 	head = NULL;
// 	check_quotes(line);
// 	line = ft_split(line, ' ');
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (line[i])
// 	{
// 		append_token_node(&head, line[i]);
// 		i++;
// 	}
// 	return (head);
// }

int main(void)
{
	char *line;

	line = "<<'terst'<<t<<<es|t\"<<<<<<<<||||||&&&&&\"ok'&&'";
	if (!check_line(line, "<>|&"))
		printf("err");
}