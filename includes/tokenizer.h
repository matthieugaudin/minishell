/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:33:32 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:33:33 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libs/libft/libft.h"

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
	bool			hdoc_quoted;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	char			*name;
	enum e_token	type;
	bool			expand;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	bool			is_here_doc;
	t_file			*files;
	int				fd_in;
	int				fd_out;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmds;
	t_token	*tokens;
	char	*line;
	int		**pipes;
}	t_data;

typedef struct s_expand_data
{
	t_data	*data;
	char	*line;
	char	*var_value;
	char	*var_name;
	int		start;
}	t_expand_data;

/*==============TOKENIZER==============*/
t_token	*tokenize_line(t_data *data, char *s);
void	set_token_type(t_token *node);
void	append_token_node(t_data *data, t_token **head, char *line);
void	set_token_prev(t_token **head, t_token *node);
int		get_total_len(t_expand_data exp);

/*=============ERROR HANDLING=============*/
void	syntax_error(t_data *data, char c);
void	free_tokens(t_token *tokens);

/*===============CHECKS===============*/
char	check_quotes(char *str);
char	check_line(char *str, char *set);

/*===============UTILS===============*/
bool	is_space(char c);
bool	is_posix_std(char c);
bool	is_quotes(t_token *node);
bool	in_quotes(char *str, int j);
bool	is_redir(enum e_token type);
bool	in_dbl_quotes(char *str, int j);
int		exit_code(int new_code, bool to_set);
void	free_list(t_env **list);
void	free_all(t_data *data, int status);
void	free_env_exp(t_env **env, t_env **exp);
void	free_data(t_data *data);

#endif /* TOKENIZER_H */