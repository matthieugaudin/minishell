#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include <stdbool.h>

typedef struct  s_file
{
    char            *name;
    enum e_token     type;
    struct s_file   *next;
}   t_file;

typedef struct s_cmd
{
    char			**args;
    bool			is_here_doc;
	t_list			*here_doc;
    t_file			*files;
    struct s_cmd	*next;
}	t_cmd;

void	expansion(t_token *node, t_env *env);
t_file	*new_file(char *name, enum e_token type);
void	add_file_back(t_file **head, t_file *new);

#endif /* PARSER_H */
