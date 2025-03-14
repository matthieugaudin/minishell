#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	t_env	*exp;
}	t_data;

/*==============UTILS==============*/
bool	is_space(char c);

/*==============ENV==============*/
char	*get_env_name(char *envp_str);
void	create_env(t_data *data, char **envp);
bool	is_posix_std(char c);
void	create_export(t_data *data);
#endif /* MINISHELL_H */
