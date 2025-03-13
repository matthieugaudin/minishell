#include "../../includes/minishell.h"

static t_env	*ft_new_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value= ft_strdup(value);
	new->next = NULL;
	return (new);
}

static void	ft_insert_node(t_env **exp, t_env *new_node)
{
	t_env	*current;

	if (!exp || !new_node)
		return;
	if (*exp == NULL || strcmp(new_node->name, (*exp)->name) < 0)
	{
		new_node->next = *exp;
		*exp = new_node;
		return;
	}
	current = *exp;
	while (current->next && strcmp(new_node->name, current->next->name) > 0)
	{
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
}

void	create_export(void)
{
	t_env	*exp;
	t_env	*cur_env;
	t_env	*new_node;
	t_env	**env;

	exp = NULL;
	env = ft_getter("env");
	if (!env)
		return ;
	cur_env = *env;
	while (cur_env)
	{
		new_node = ft_new_node(cur_env->name, cur_env->value);
		if (!new_node)
			return ;
		ft_insert_node(&exp, new_node);
		cur_env = cur_env->next;
	}
	ft_setter(exp, "exp");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/minishell.h"

/* Fonction utilitaire pour afficher une liste d'environnement */
void print_list(t_env *list)
{
    while (list)
    {
        /* Affiche sous la forme "NOM=VALUE" ; si value est NULL, affiche NOM= */
        if (list->value)
            printf("%s=%s\n", list->name, list->value);
        else
            printf("%s=\n", list->name);
        list = list->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env **env;
    t_env **exp;

    /* Création de la liste env à partir de envp */
    create_env(envp);

    /* Création de la liste export en faisant une copie triée de env */
    create_export();

    /* Récupération des pointeurs sur les listes via ft_getter */
    env = ft_getter("env");
    exp = ft_getter("exp");

    if (!env || !exp)
    {
        fprintf(stderr, "Erreur lors de la récupération des listes.\n");
        return (EXIT_FAILURE);
    }

    /* Selon la présence d'arguments, on affiche l'une ou l'autre des listes */
    if (argc == 1)
    {
        printf("Liste env :\n");
        print_list(*env);
        printf("\nListe export :\n");
        print_list(*exp);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "env") == 0)
        {
            printf("Liste env :\n");
            print_list(*env);
        }
        else if (strcmp(argv[1], "exp") == 0)
        {
            printf("Liste export :\n");
            print_list(*exp);
        }
        else
        {
            printf("Usage: %s [env|exp]\n", argv[0]);
        }
    }
    else
    {
        printf("Usage: %s [env|exp]\n", argv[0]);
    }
    return (EXIT_SUCCESS);
}
