/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 10:20:20 by mgaudin          ###   ########.fr       */
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

// t_token	*tokenizer(char *str);
char	**split_quotes(char const *s);

#endif /* TOKENIZER_H */