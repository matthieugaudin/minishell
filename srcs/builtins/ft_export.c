#include "../../includes/builtins.h"

static int	ft_find_egal_pos(char *str)
{
	int	i;

	if (!str || !*str)
		return (-1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		if (!is_posix_std(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

static void	ft_plus_option(t_env **env, t_env **exp, char *name, char *value)
{
	t_env	*node;
	char	*new_value;

	if (!env || !exp || !name)
		return ;
	node = *env;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
		{
			new_value = ft_strjoin(node->value, value);
			free(node->value);
			node->value = new_value;
			ft_update_exp_node(exp, ft_new_node(name, new_value));
			return ;
		}
		node = node->next;
	}
	ft_update_env_node(env, ft_new_node(name, value));
	ft_update_exp_node(exp, ft_new_node(name, value));
}

static int	ft_update_env_exp(t_data *data, char *arg, size_t i_egal)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, i_egal);
	if (!arg[i_egal + 1])
		value = NULL;
	if (arg[i_egal] == '+')
		i_egal++;
	value = ft_substr(arg, i_egal + 1, ft_strlen(arg) - i_egal - 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (1);
	}
	if (arg[i_egal - 1] == '+')
		ft_plus_option(&data->env, &data->exp, name, value);
	else
	{
		ft_update_env_node(&data->env, ft_new_node(name, value));
		ft_update_exp_node(&data->exp, ft_new_node(name, value));
	}
	free(name);
	free(value);
	return (0);
}

static void	display_export(t_env *exp)
{
	while (exp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp->name, 1);
		if (exp->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(exp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		exp = exp->next;
	}
}

int	ft_export(t_data *data, char **args, bool exit)
{
	int	i;
	int	i_egal;
	int	ret;

	i = 0;
	ret = 0;
	if (!args || !args[0])
		display_export(data->exp);
	while (args && args[i])
	{
		i_egal = ft_find_egal_pos(args[i]);
		if (i_egal == -1)
		{
			print_export_error(args[i]);
			ret = 1;
		}
		else if (i_egal == 0)
			ft_update_exp_node(&data->exp, ft_new_node(args[i], NULL));
		else
			ft_update_env_exp(data, args[i], i_egal);
		i++;
	}
	return (value(ret, exit));
}
