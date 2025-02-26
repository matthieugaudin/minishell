/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:53:35 by mgaudin          ###   ########.fr       */
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
char	**split_quotes(char *s);
char	**split_tokens(char *s);
bool	in_quotes(char *str, int j);
bool	check_quotes(char *str);
bool	check_line(char *str, char *set);
int		fill_tab(char **tab, char *s);

#endif /* TOKENIZER_H */