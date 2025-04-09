#include "../../includes/parser.h"

char	*get_var_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->name, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
