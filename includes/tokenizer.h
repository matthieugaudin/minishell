/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/24 21:27:16 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*
do i need a token for builtins ?
*/

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
	char				*value;
	enum e_token		type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_cmd
{
	
}	t_cmd;

t_token	*tokenizer(char *str);
char	**split_tokens(char const *s);
void	append_token_node(t_token **head, char *line);
void	set_token_prev(t_token **head, t_token *node);
void	set_token_type(t_token *node);

#endif /* TOKENIZER_H */