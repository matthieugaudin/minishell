/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/22 20:40:32 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../includes/errors.h"

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

I think we have to keep things simple
-> check unexpected tokens
-> split the line returned by readline (harder part)
-> append a node for each string splitted with good value and token
-> convert token list to a comd list that will be send to the parsing 

- ckeck unclosed quotes : OK but to test
- check unexpected token >>> or <<<
- ckeck unexpexted token ||
- how to treat  & && &&& tokens : i think in quotes it's like an arg so do not prevent
and outside quotes as an unexpected token because with bash :
- cat -e & -> problem so i don't have to manage this
- cat -e && -> bonus part i don't have to check that
- cat -e &&& -> invalid token
- cat -e '&' -> invalid option

The objetif is to keep a simple logic
- if not a valid token send error and stop
- split the args and remember
	-> prevent quotes from interpreting any special caracter, bet it : | < << > >> '' "" ;
	-> sticked quotes are just an arg
	-> a string with severals quotes also interpret | < > if outside of the quote

< infile1 cat -e||grep >> ok -> unexpected token

< infile1 cat -e|'<<<'grep >> ok
- <
- infile1
- cat
- -e
- |
- <<<grep
- >>
- ok

< infile1 cat "-e'||'grep" >> ok
- <
- infile1
- cat
- -e'||'grep
- >>
- ok

< infile1 cat "-e'||'gre">"p" >> ok
- <
- infile1
- cat
- -e'||'gre
- >
- p
- >>
- ok

< infile1 cat -e|"grep" ok >> ok
- <
- infile1
- cat
- -e
- |
- grep
- ok
- >>
- ok

*/