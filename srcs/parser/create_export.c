#include "../../includes/parser.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return;
	free(node->name);
	free(node->value);
	free(node);
}

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	if (name)
		new->name = ft_strdup(name);
	if (value)
		new->value= ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_update_exp_node(t_env **exp, t_env *new_node)
{
	t_env	*current;

	if (!exp || !new_node)
		return ;
	if (*exp == NULL || ft_strcmp(new_node->name, (*exp)->name) < 0)
	{
		new_node->next = *exp;
		*exp = new_node;
		return ;
	}
	current = *exp;
	while (current->next && ft_strcmp(new_node->name, current->next->name) >= 0)
	{
		if (new_node->value && ft_strcmp(new_node->name, current->name) == 0)
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

t_env	*create_export(t_env *env)
{
	t_env	*exp;
	t_env	*cur_env;
	t_env	*new_node;

	if (!env)
		return (NULL);
	exp = malloc(sizeof(t_env));
	if (!exp)
		return (NULL);
	exp = NULL;
	cur_env = env;
	while (cur_env)
	{
		if (ft_strcmp(cur_env->name, "_") != 0)
		{
			new_node = ft_new_node(cur_env->name, cur_env->value);
			if (!new_node)
				return (NULL);
			ft_update_exp_node(&exp, new_node);
		}
		cur_env = cur_env->next;
	}
	return (exp);
}








// #include "../../includes/minishell.h"

// int	count_list_nodes(t_env *list)
// {
//     int		count;
//     t_env	*tmp;

//     count = 0;
//     tmp = list;
//     while (tmp)
//     {
//         count++;
//         tmp = tmp->next;
//     }
//     return (count);
// }

// void	compare_lists(char **envp, t_data *data)
// {
//     int		system_count = 0;
//     int		env_count = count_list_nodes(data->env);
//     int		exp_count = count_list_nodes(data->exp);
//     char	**system_vars = envp;

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
//     int		missing = 0;
//     int		diff_value = 0;
//     char	**envp_ptr = envp;

//     while (*envp_ptr)
//     {
//         char	*eq = strchr(*envp_ptr, '=');
//         char	*true_name = strndup(*envp_ptr, eq - *envp_ptr);
//         char	*true_value = eq + 1;
//         t_env	*node = data->env;
//         bool	found = false;

//         while (node)
//         {
//             if (strcmp(true_name, node->name) == 0)
//             {
//                 found = true;
//                 if (strcmp(true_value, node->value) != 0)
//                     diff_value++;
//                 break ;
//             }
//             node = node->next;
//         }
//         if (!found && strcmp(true_name, "_") != 0)
//             missing++;
//         free(true_name);
//         envp_ptr++;
//     }

//     // Vérification tri EXPORT
//     int		sorted = true;
//     t_env	*current = data->exp;
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

// int	main(int argc, char **argv, char **envp)
// {
//     t_data	*data = malloc(sizeof(t_data));

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

//     return (0);
// }

