#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "../libs/libft/libft.h"
# include "parser.h"


/*
dup stdin and stdout
*/
typedef struct s_data
{
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmds;
	int		**pipes;
	char	*path;
	int		status;
}	t_data;

/*==============UTILS==============*/
bool	is_space(char c);

/*==============ENV==============*/

char	*get_env_name(char *envp_str);
void	create_env(t_data *data, char **envp);
bool	is_posix_std(char c);
void	create_env(t_data *data, char **envp);
void	create_export(t_data *data);

#endif /* EXECUTION_H */
