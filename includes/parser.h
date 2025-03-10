#ifndef PARSER_H
# define PARSER_H

#include "libs/libft/libft.h"
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

void	expansion(t_token *node, char **envp);

#endif /* PARSER_H */