#include "../../includes/parser.h"

static t_expand_data	create_expand_tkn(t_data *data,
	t_env *env, t_token *node, int start)
{
	t_expand_data	res;

	res.data = data;
	res.line = node->value;
	res.var_name = get_env_name(data, res.line + start);
	res.var_value = get_var_value(env, res.var_name);
	res.start = start;
	return (res);
}

static void	expand_var(t_data *data, t_token *node, t_env *env, int start)
{
	t_expand_data	exp;
	int				len;
	char			*res;
	int				value_len;
	int				remainder;

	exp = create_expand_tkn(data, env, node, start);
	len = get_total_len(exp);
	value_len = ft_strlen(exp.var_value);
	remainder = ft_strlen(exp.line + start + ft_strlen(exp.var_name));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(exp.var_name);
		free_all(data, EXIT_FAILURE);
	}
	ft_strlcpy(res, node->value, start);
	if (exp.var_value)
		ft_strlcat(res + start - 1, exp.var_value, value_len + 1);
	ft_strlcat(res + start - 1 + value_len, node->value + start
		+ ft_strlen(exp.var_name), remainder + 1);
	free(node->value);
	free(exp.var_name);
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
	ft_strlcat(res + start - 1 + code_len, node->value
		+ start + 1, remainder + 1);
	free(node->value);
	node->value = res;
	free(code);
}

static bool	handle_expand(t_data *data, t_token *node, t_env *env, int i)
{
	char	*str;

	str = node->value;
	if (str[i + 1] == '?')
		expand_exit(data, node, i + 1);
	else if (ft_isdigit(str[i + 1]))
		expand_digit_tkn(data, node, i + 1);
	else if (!(node->prev && node->prev->type == HERE_DOC)
		&& str[i + 1]
		&& !(in_dbl_quotes(str, i)
			&& (str[i + 1] == '\"' || str[i + 1] == '\''))
		&& (is_posix_std(str[i + 1])
			|| (str[i + 1] == '\"' || str[i + 1] == '\'')))
		expand_var(data, node, env, i + 1);
	else
		return (false);
	return (true);
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
				if (handle_expand(data, node, env, i))
				{
					str = node->value;
					i = -1;
				}
			}
			i++;
		}
		node = node->next;
	}
}
