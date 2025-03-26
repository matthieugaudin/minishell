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
		if (!is_posix_std(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

static int ft_update_env_exp(t_data *data, char *arg, size_t i_egal)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, i_egal);
	value = ft_substr(arg, i_egal + 1, ft_strlen(arg) - i_egal - 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (1);
	}
	ft_update_env_node(&data->env, ft_new_node(name, value));
	ft_update_exp_node(&data->exp, ft_new_node(name, value));
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

static void	print_export_error(char *str)
{
	ft_putstr_fd("export: '", 2);
    ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int ft_export(t_data *data, char **args)
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
	return (ret);
}




// void	print_data(t_env *env)
// {
// 	printf("#######\tENV\t#######\n\n");
// 	while (env != NULL)
// 	{
// 		printf("%s=%s\n", env->name, env->value);
// 		env = env->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	char	*args[] = {"salut=\"wow\"", "cava=wow", NULL};
// 	char	*args_two[] = {"salut", "cava", NULL};

// 	data = malloc(sizeof(t_data));
// 	(void)argc;
// 	(void)argv;
// 	data->env = create_env(envp);
// 	data->exp = create_export(data->env);

// 	// ft_export(data, args);
// 	// ft_export(data, NULL);
// 	ft_export(data, args);
// 	print_data(data->env);
// 	printf("\n\n\n\n");
// 	ft_export(data, NULL);
// 	printf("\n\n\n\n");
// 	ft_unset(data, args_two);
// 	ft_export(data, NULL);
// 	printf("\n\n\n\n");
// 	print_data(data->env);
// 	return (0);
// }
