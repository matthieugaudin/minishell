#include "../../includes/minishell.h"
#include "../../includes/parser.h"

// open every files and handle here_doc
// fork for every cmd
//      -> find the executable
//         if cmd not found it juste skip the redirection and exece
//      -> redirect fds
//      -> check if there is a builtin
//      -> exec command
//      -> wait for all processes

void    execution(t_cmd *cmds)
{

}
