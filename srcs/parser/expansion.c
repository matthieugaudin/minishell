#include "../../includes/execution.h"
#include "../../includes/tokenizer.h"

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

void	expand_var(t_token *node, t_env *env, int start)
{
	char	*var_value;
	char	*var_name;
	char	*res;
	int		value_len;
	int		name_len;
	int		remainder;
	int		len;

	var_name = get_env_name(node->value + start);
	var_value = get_var_value(env, var_name);
	value_len = ft_strlen(var_value);
	name_len = ft_strlen(var_name);
	remainder = ft_strlen(node->value + start + ft_strlen(var_name));
	len = (start - 1) + value_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(res, node->value, start);
	if (var_value)
		ft_strlcat(res + start - 1, var_value, value_len + 1);
	ft_strlcat(res + start - 1 + value_len, node->value + start + name_len, remainder + 1);
	free(node->value);
	node->value = res;
}

void	expansion(t_token *node, t_env *env)
{
	char	*str;
	int		i;

	while (node)
    {
		i = 0;
		str = node->value;
		while (str[i])
		{
			if (str[i] == '$' && (!in_quotes(str, i) || in_dbl_quotes(str, i))
				&& !(node->prev && node->prev->type == HERE_DOC)
				&& (!is_space(str[i + 1]) && str[i + 1] != '\0'
				&&!(in_dbl_quotes(str, i) && str[i + 1] == '\"')))
			{
				expand_var(node, env, i + 1);
				str = node->value;
				i = -1;
			}
			i++;
		}
		node = node->next;
    }
}
