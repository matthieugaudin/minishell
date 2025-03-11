#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

/*
- links with echo $?
- how to handle builtins
*/

enum e_file
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
};

typedef struct  s_file
{
    char       *name;
    enum e_file  type;
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

#endif /* PARSER_H */