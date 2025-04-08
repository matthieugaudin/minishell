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

static void	expand_var(t_data *data, t_token *node, t_env *env, int start)
{
	char	*var_value;
	char	*var_name;
	char	*res;
	int		value_len;
	int		name_len;
	int		remainder;
	int		len;

	var_name = get_env_name(data, node->value + start);
	var_value = get_var_value(env, var_name);
	value_len = ft_strlen(var_value);
	name_len = ft_strlen(var_name);
	remainder = ft_strlen(node->value + start + ft_strlen(var_name));
	len = (start - 1) + value_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(var_name);
		free_all(data, EXIT_FAILURE);
	}
	ft_strlcpy(res, node->value, start);
	if (var_value)
		ft_strlcat(res + start - 1, var_value, value_len + 1);
	ft_strlcat(res + start - 1 + value_len, node->value + start + name_len, remainder + 1);
	free(node->value);
	free(var_name);
	node->value = res;
}

static void	expand_exit(t_data *data, t_token *node, int start)
{
	char	*res;
	char	*code;
	int		code_len;
	int		remainder;
	int		len;

	code = ft_itoa(exit_code(0, false));
	if (!code)
		free_all(data, EXIT_FAILURE);
	code_len = ft_strlen(code);
	remainder = ft_strlen(node->value + start + 1);
	len = (start - 1) + code_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(code);
		free_all(data, EXIT_FAILURE);
	}
	ft_strlcpy(res, node->value, start);
	ft_strlcat(res + start - 1, code, code_len + 1);
	ft_strlcat(res + start - 1 + code_len, node->value + start + 1, remainder + 1);
	free(node->value);
	node->value = res;
	free(code);
}

static void	expand_digit(t_data *data, t_token *node, int start)
{
	char	*res;
	int		remainder;
	int		len;

	len = ft_strlen(node->value) - 2;
	remainder = ft_strlen(node->value + start + 1);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		free_all(data, EXIT_FAILURE);
	ft_strlcpy(res, node->value, start);
	ft_strlcat(res + start - 1, node->value + start + 1, remainder + 1);
	free(node->value);
	node->value = res;
}

void	expand_tokens(t_data *data, t_token *node, t_env *env)
{
	char	*str;
	int		i;

	while (node)
    {
		i = 0;
		str = node->value;
		while (str[i])
		{
			if (str[i] == '$' && (!in_quotes(str, i) || in_dbl_quotes(str, i)))
			{
				if (str[i + 1] == '?')
					expand_exit(data, node, i + 1);
				else if (ft_isdigit(str[i + 1]))
					expand_digit(data, node, i + 1);
				else if (!(node->prev && node->prev->type == HERE_DOC)
					&& str[i + 1]
					&& !(in_dbl_quotes(str, i) && (str[i + 1] == '\"' || str[i + 1] == '\''))
					&& (is_posix_std(str[i + 1]) || (str[i + 1] == '\"' || str[i + 1] == '\'')))
					expand_var(data, node, env, i + 1);
				else
				{
					i++;
					continue;
				}
				str = node->value;
				i = -1;
			}
			i++;
		}
		node = node->next;
    }
}
