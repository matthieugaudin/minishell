#include "../../includes/builtins.h"

static bool	is_n_option(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[i] != '-')
		return (false);
	i = 1;
	if (!str[i])
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	ft_echo(char **args)
{
	size_t	i;
	bool	is_n;

	if (!args || !args[0])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i = 1;
	is_n = false;
	while (args[i] && is_n_option(args[i]))
	{
		is_n = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
	return (0);
}

// int main(void)
// {
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t nread;

//     while (1)
//     {
//         // Afficher le prompt et lire la saisie
//         printf("minishell$ ");
//         nread = getline(&line, &len, stdin);
//         if (nread == -1)
//         {
//             perror("getline");
//             break;
//         }
//         // Supprime le saut de ligne terminal
//         if (line[nread - 1] == '\n')
//             line[nread - 1] = '\0';

//         // Permet de quitter le shell avec "exit"
//         if (strcmp(line, "exit") == 0)
//             break;

//         // Tokenizer la ligne en arguments (on se base sur l'espace)
//         char **args = NULL;
//         int args_count = 0;
//         char *token = strtok(line, " ");
//         while (token != NULL)
//         {
//             // Réallouer le tableau pour ajouter le token
//             args = realloc(args, sizeof(char *) * (args_count + 1));
//             if (!args)
//             {
//                 perror("realloc");
//                 exit(EXIT_FAILURE);
//             }
//             args[args_count] = token;
//             args_count++;
//             token = strtok(NULL, " ");
//         }
//         // Ajout d'un pointeur NULL terminant le tableau d'arguments
//         args = realloc(args, sizeof(char *) * (args_count + 1));
//         args[args_count] = NULL;

//         // Vérification sur la commande : ici on teste uniquement pour "echo"
//         if (args_count > 0)
//         {
//             if (strcmp(args[0], "echo") == 0)
//             {
//                 ft_echo(args);
//             }
//             else
//             {
//                 printf("Commande non reconnue: %s\n", args[0]);
//             }
//         }

//         // Libération du tableau d'arguments alloué (les tokens eux-mêmes pointent sur la ligne)
//         free(args);
//     }

//     free(line);
//     return 0;
// }

