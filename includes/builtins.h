#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include <limits.h>
# include "execution.h"

void	ft_exit(t_data* data, char **args, int stdin, int stdout, bool to_exit);
int			ft_pwd(bool exit);
int	        ft_echo(char **args, bool exit);
int	        value(int status, bool to_exit);
int 	    ft_cd(t_data *data, char *args, bool exit);
int 	    ft_env(t_env *env, char **args, bool exit);
int 		ft_unset(t_data *data, char **args, bool exit);
int         ft_export(t_data *data, char **args, bool exit);

#endif /* BUILTINS_H */
