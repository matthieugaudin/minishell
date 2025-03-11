#include "../../includes/minishell.h"
<<<<<<< HEAD

bool is_posix_std(char c)
{
	if (ftisalnum(c) || c == '_')
=======
#include "../../includes/tokenizer.h"

/*
Verifies that a character follows the posix standards,
meaning that it's an uppercase/lowercase letter, a digit,
or an underscore.
*/
bool	is_posix_std(char c)
{
	if (ft_isalnum(c) || c == '_')
>>>>>>> main
		return (true);
	else
		return (false);
}

<<<<<<< HEAD
char *get_var_name(char *env_var)
{
	char *var_name;
	int i;

	i = 0;
	while (is_posix_std(env_var[i]))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var_name, env_var, i + 1);
	return (var_name);
}

void append_env_node(t_env **env, char *str)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (*env == NULL)
		*env = node;
	node->name = get_var_name(str);
	node->value = get_var_value(str);
	// set the prev node next to the new one
	node->next = NULL;
}

void parse_envp(char **envp)
{
	size_t i;
	t_env *env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		append_env_node(&env, envp[i]);
		i++;
	}
=======
/*
Takes an environment variable from envp and returns its name.
*/
char	*get_env_name(char *envp_str)
{
	char	*env_name;
	int		i;

	i = 0;
	while (is_posix_std(envp_str[i]))
		i++;
	env_name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(env_name, envp_str, i + 1);
	return (env_name);
}

char	*get_env_value(char *envp_str)
{
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	while (is_posix_std(envp_str[i]))
		i++;
	i++;
	j = 0;
	while (envp_str[i + j])
		j++;
	env_value = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(env_value, envp_str + i, j + 1);
	return (env_value);
}

void	append_env_node(t_env **env, char *envp)
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->name = get_env_name(envp);
	node->value = get_env_value(envp);
	node->next = NULL;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	last_node = *env;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
}

t_env   *create_env(char **envp)
{
    t_env	*env;

	env = NULL;
	while (*envp)
	{
		append_env_node(&env, *envp);
		envp++;
	}
	return (env);
>>>>>>> main
}
