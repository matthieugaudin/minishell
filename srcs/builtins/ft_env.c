#include "../../includes/builtins.h"

int	ft_env(t_env *env, char **args)
{
	if (args && args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (127);
	}
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=", 1);
		if (env->value)
			ft_putendl_fd(env->value, 1);
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
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
