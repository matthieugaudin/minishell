#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

/*
Verifies that a character follows the posix standards,
meaning that it's an uppercase/lowercase letter, a digit,
or an underscore.
*/
bool	is_posix_std(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

/*
Takes an environment variable from envp and returns its name.
*/
char	*get_var_name(char *env_var)
{
	char	*var_name;
	int		i;

	i = 0;
	while (is_posix_std(env_var[i]))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var_name, env_var, i + 1);
	return (var_name);
}

char	*get_var_value(char **envp, char *var_name)
{
	char	*var_value;
	char	*envp_name;
	int		i;

	i = 0;
	var_value = NULL;
	envp_name = NULL;
	while (*envp)
	{
		envp_name = get_var_name(*envp);
		if (ft_strcmp(envp_name, var_name) == 0)
		{
			while (is_posix_std(*((*envp) + i)))
				i++;
			var_value = ((*envp) + i + 1);
			break ;
		}
		envp++;
	}
	return (var_value);
}

void	expand_var(t_token *node, char **envp, int start)
{
	char	*var_value;
	char	*var_name;
	int		remainder;
	int		len;

	var_name = get_var_name(node->value + start);
	var_value = get_var_value(envp, var_name);
	remainder = ft_strlen(node->value + start + ft_strlen(var_name));
	len = (start - 1) + ft_strlen(var_value) + remainder;
	printf("%d\n", len);
}



void	expansion(t_token *node, char **envp)
{
	char	*str;
	int		i;

	(void)envp;
	while (node)
    {
		i = 0;
		str = node->value;
		while (str[i])
		{
			if (str[i] == '$' && (!in_quotes(str, i) || in_dbl_quotes(str, i)))
				expand_var(node, envp, i + 1);
			i++;
		}
		node = node->next;
    }
}

// segfault : "ok\"$USE'R\"ok"
// "OK\"'$USER''\"ok"
// "ok$USE'R'ok"

int main(int argc, char **argv, char **envp)
{
	t_token *head;

	(void)argc;
	(void)argv;

	head = tokenizer("ok\"$USERR\"ok");
	expansion(head, envp);
}
