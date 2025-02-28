/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/28 18:01:48 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

bool	special_car(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

t_token	*tokenizer(char *s)
{
	t_token	*head;
	char	*value;
	int		len;
	int		i;

	head = NULL;
	check_unexpected(s);

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == ' ')
			s++;
		while (*s && (*s != ' ' || (*s == ' ' && in_quotes(s - i, i)))
			&& (!special_car(*s) || (special_car(*s) && in_quotes(s - i, i))))
		{
			i++;
			s++;
			len++;
		}
		if (len == 0 && special_car(*s) && !in_quotes(s - i, i))
		{
			s++;
			i++;
			len++;
			if (special_car(*s) && *s == *(s - 1)
				&& (*s == '<' || *s == '>'))
			{
				i++;
				s++;
				len++;
			}
		}
		if (*s)
		{				
			value = malloc((len + 1) * sizeof(char));
			ft_strlcat(value, s - len, len + 1);
			append_token_node(&head, value);
		}
	}
	return (head);
}

void test(void)
{
	
}