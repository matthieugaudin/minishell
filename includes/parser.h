#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

/*
- links with echo $?
- how to handle builtins
*/

typedef struct s_cmd
{
    int				pipe;
    char			**args;
    bool			is_here_doc;
	t_list			here_doc;
    t_list			*infile;
    t_list			*outfile;
    struct s_cmd	*next;
}	t_cmd;

void	expansion(t_token *node, t_env *env);

#endif /* PARSER_H */