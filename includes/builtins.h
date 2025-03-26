#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include "execution.h"

int			ft_pwd(void);
int			ft_env(t_env *env);
int			ft_echo(char **args);
int 		ft_unset(t_data *data, char **args);

#endif /* BUILTINS_H */
