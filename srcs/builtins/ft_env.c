#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
	return (0);
}

// int main(void)
// {
//     // Allocation des noeuds de la liste
//     t_env *env1 = malloc(sizeof(t_env));
//     t_env *env2 = malloc(sizeof(t_env));
//     t_env *env3 = malloc(sizeof(t_env));

//     if (!env1 || !env2 || !env3)
//     {
//         // En cas d'erreur d'allocation, on quitte le programme
//         return (1);
//     }

//     // Initialisation des noeuds avec des variables d'environnement fictives
//     env1->name = "PATH";
//     env1->value = "/usr/bin:/bin";
//     env1->next = env2;

//     env2->name = "HOME";
//     env2->value = "/home/user";
//     env2->next = env3;

//     env3->name = "SHELL";
//     env3->value = "/bin/bash";
//     env3->next = NULL;

//     // Affichage de l'environnement
//     ft_env(env1);

//     // Libération de la mémoire allouée
//     free(env1);
//     free(env2);
//     free(env3);

//     return (0);
// }
