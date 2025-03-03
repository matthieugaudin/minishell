/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/03 13:10:33 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

enum e_token
{
	COMMAND,
	FILE_T,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC
};

typedef struct s_token
{
	char			*value;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*tokenizer(char *line);
void	append_token_node(t_token **head, char *line);
void	set_token_prev(t_token **head, t_token *node);
void	set_token_type(t_token *node);
bool	in_quotes(char *str, int j);
bool	check_quotes(char *str);
bool	check_line(char *str, char *set);
void	check_unexpected(char *s);
bool	special_car(char c);

#endif /* TOKENIZER_H */