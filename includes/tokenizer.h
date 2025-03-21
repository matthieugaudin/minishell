#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>

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

/*==============TOKENIZER==============*/
t_token	*tokenizer(char *line);

/*==============TOKEN LIST=============*/
void	append_token_node(t_token **head, char *line);
void	set_token_prev(t_token **head, t_token *node);
void	set_token_type(t_token *node);

/*===============CHECKS===============*/
char	check_quotes(char *str);
char	check_line(char *str, char *set);
void	syntax_error(t_token *tokens, char c);
void	free_tokens(t_token *tokens, bool alloc_err);

/*===============UTILS===============*/
bool	in_quotes(char *str, int j);
bool	in_dbl_quotes(char *str, int j);
bool	special_car(char c);

#endif /* TOKENIZER_H */
