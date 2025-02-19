/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:43:05 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/19 11:52:36 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

enum s_token
{
	COMMAND,
	OPTION,
	PIPE,
	FILE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
};

typedef struct s_cmd
{
	s_token			type;
	char			*value;
	struct s_cmd	*next;
}	t_cmd;


#endif /* TOKENIZER_H */