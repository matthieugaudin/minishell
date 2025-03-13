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

/*==============ENV==============*/\

void	create_env(char **envp);
bool	is_posix_std(char c);
void	ft_setter(t_env *set, char *str);
t_env	**ft_getter(char *str);

#endif /* MINISHELL_H */
