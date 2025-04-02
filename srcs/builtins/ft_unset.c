#include "../../includes/builtins.h"

static bool is_valid_name(char *str)
{
    int	i;

	i = 1;
	if (!str || !*str)
        return (false);
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (false);
    while (str[i])
    {
        if (!is_posix_std(str[i]))
            return (false);
        i++;
    }
    return (true);
}

static void	ft_check_and_remove(char *str, t_env **head)
{
	t_env *prev;
	t_env *current;

	if (!head || !*head)
		return ;
	if (ft_strcmp((*head)->name, str) == 0)
	{
		current = *head;
		*head = (*head)->next;
		free_env_node(current);
		return;
	}
	prev = *head;
	current = (*head)->next;
	while (current)
	{
		if (ft_strcmp(current->name, str) == 0)
		{
			prev->next = current->next;
			free_env_node(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

static void	print_unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: '", 2);
    ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_unset(t_data *data, char **args)
{
	size_t i;
	int		ret;

	if (!args || !args[0])
		return (0);
	i = 0;
	ret = 0;
	while (args[i])
	{
		if (!is_valid_name(args[i]))
		{
			print_unset_error(args[i]);
            ret = 1;
		}
		else
		{
			if (data->env)
				ft_check_and_remove(args[i], &data->env);
			if (data->exp)
				ft_check_and_remove(args[i], &data->exp);
		}
		i++;
	}
	return (ret);
}







// #include "../../includes/minishell.h"

// int count_list_nodes(t_env *list)
// {
//     int count;
//     t_env *tmp;

//     count = 0;
//     tmp = list;
//     while (tmp)
//     {
//         count++;
//         tmp = tmp->next;
//     }
//     return (count);
// }

// void compare_lists(char **envp, t_data *data)
// {
//     int system_count = 0;
//     int env_count = count_list_nodes(data->env);
//     int exp_count = count_list_nodes(data->exp);
//     char **system_vars = envp;

//     // Comptage des variables système
//     while (*system_vars)
//     {
//         system_count++;
//         system_vars++;
//     }

//     // Vérification comptage de base
//     printf("\n=== COMPARAISON ===\n");
//     printf("Variables système : %d\n", system_count);
//     printf("Variables ENV     : %d\n", env_count);
//     printf("Variables EXPORT  : %d\n", exp_count);

//     // Vérification contenu ENV
//     int missing = 0;
//     int diff_value = 0;
//     char **envp_ptr = envp;

//     while (*envp_ptr)
//     {
//         char *eq = strchr(*envp_ptr, '=');
//         char *true_name = strndup(*envp_ptr, eq - *envp_ptr);
//         char *true_value = eq + 1;
//         t_env *node = data->env;
//         bool found = false;

//         while (node)
//         {
//             if (strcmp(true_name, node->name) == 0)
//             {
//                 found = true;
//                 if (strcmp(true_value, node->value) != 0)
//                     diff_value++;
//                 break;
//             }
//             node = node->next;
//         }
//         if (!found && strcmp(true_name, "_") != 0)
//             missing++;
//         free(true_name);
//         envp_ptr++;
//     }

//     // Vérification tri EXPORT
//     int sorted = true;
//     t_env *current = data->exp;
//     while (current && current->next)
//     {
//         if (strcmp(current->name, current->next->name) > 0)
//             sorted = false;
//         current = current->next;
//     }

//     // Affichage résultats
//     printf("\nVariables manquantes dans ENV : %d", missing);
//     printf("\nVariables de valeur différente : %d", diff_value);
//     printf("\nEXPORT trié correctement : %s\n", sorted ? "OUI" : "NON");

//     if (missing == 0 && diff_value == 0 && sorted)
//         printf("\n\x1b[32mTESTS PASSÉS AVEC SUCCÈS\x1b[0m\n");
//     else
//         printf("\n\x1b[31mPROBLÈMES DÉTECTÉS\x1b[0m\n");
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_data *data = malloc(sizeof(t_data));

//     (void)argc;
//     (void)argv;
//     create_env(data, envp);

//     printf("=== VARIABLES SYSTÈME ===\n");
//     for (char **e = envp; *e; e++)
//         printf("%s\n", *e);

//     printf("\n=== VARIABLES ENV ===\n");
//     for (t_env *e = data->env; e; e = e->next)
//         printf("%s=%s\n", e->name, e->value);

//     printf("\n=== VARIABLES EXPORT ===\n");
//     for (t_env *e = data->exp; e; e = e->next)
//         printf("%s=%s\n", e->name, e->value);
//     compare_lists(envp, data);
// 	char *args[] =
// 	{
// 		"PATH",
// 		"ca",
// 		"va",
// 		NULL
// 	};
// 	ft_unset(data, args);
// 	compare_lists(envp, data);
// 	t_env	*tmp;
// 	while (data->env)
// 	{
// 		free(data->env->name);
// 		free(data->env->value);
// 		tmp = data->env->next;
// 		free(data->env);
// 		data->env = tmp;
// 	}
// 	while (data->exp)
// 	{
// 		free(data->exp->name);
// 		free(data->exp->value);
// 		tmp = data->exp->next;
// 		free(data->exp);
// 		data->exp = tmp;
// 	}
// 	free(data);
// 	return (0);
// }
