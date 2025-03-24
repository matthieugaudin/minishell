#include "../../includes/builtins.h"

static int	ft_find_egal_pos(char *str)
{
	size_t	i;

	if (!str || !*str || ft_isdigit(str[0]))
		return (-1);
	i = 0;
	while (str[i])
	{
		if (!is_posix_std(str[i]))
			return (-1);
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static void ft_update_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return;
	if (*env == NULL)
	{
		new_node->next = *env;
		*env = new_node;
		return;
	}
	current = *env;
	while (current->next)
	{
		if (new_node->value && strcmp(new_node->name, current->name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_node->value);
			free_env_node(new_node);
			return ;
		}
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
	return ;
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
	ft_insert_exp_node(&data->exp, ft_new_node(name, value));
	ft_update_env_node(&data->env, ft_new_node(name, value));
	free(name);
	free(value);
	return (0);
}

int ft_export(t_data *data, char **args)
{
	size_t	i;
	size_t	i_egal;

	i = 0;
	while (args[i])
	{
		i_egal = ft_find_egal_pos(args[i]);
		printf("i_egal : %zu\n", i_egal);
		if (i_egal == 0)
			ft_insert_exp_node(&data->exp, ft_new_node(args[i], NULL));
		else if (i_egal > 0)
			ft_update_env_exp(data, args[i], i_egal);
		i++;
	}
	return (0);
}

// void	print_data(t_env *env, t_env *exp)
// {
// 	printf("#######\tENV\t#######\n\n");
// 	while (env != NULL)
// 	{
// 		printf("%s=%s\n", env->name, env->value);
// 		env = env->next;
// 	}
// 	printf("\n\n#######\tEXP\t#######\n\n");
// 	while (exp != NULL)
// 	{
// 		printf("%s=%s\n", exp->name, exp->value);
// 		exp = exp->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	char	*args[] = {"salut", "cava", NULL};

// 	data = malloc(sizeof(t_data));
// 	(void)argc;
// 	(void)argv;
// 	data->env = create_env(envp);
// 	data->exp = create_export(data->env);

// 	ft_export(data, args);
// 	print_data(data->env, data->exp);
// 	return (0);
// }
