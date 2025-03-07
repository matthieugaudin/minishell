/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/07 10:43:38 by mgaudin          ###   ########.fr       */
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

/*==============TOKENIZER==============*/
t_token	*tokenizer(char *line);

/*==============TOKEN LIST=============*/
void	append_token_node(t_token **head, char *line);
void	set_token_prev(t_token **head, t_token *node);
void	set_token_type(t_token *node);

/*===============CHECKS===============*/
char	check_quotes(char *str);
char	check_line(char *str, char *set);
void	send_token_err(char c);

/*===============UTILS===============*/
bool	in_quotes(char *str, int j);
bool	in_dbl_quotes(char *str, int j);
bool	special_car(char c);

#endif /* TOKENIZER_H */