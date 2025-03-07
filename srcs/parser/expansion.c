/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:55:36 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/07 11:51:36 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		get_var_len(char *str, int start)
{
	int	i;

	i = 0;
	while (is_posix_std(str[start + i]))
	{
		i++;
	}
	return (i);
}

char	*get_env_var(char *str, char **envp)
{
	char	*envp_name;
	char	*str_name;

	while (*envp)
	{
		envp_name = get_var_name(*envp);
		str_name = get_var_name(str);
		if (ft_strcmp(envp_name, str_name) == 0)
			return (*envp);
		envp++;
	}
	free(envp_name);
	free(str_name);
	return (NULL);
}

void	expand_var(t_token *node, char **envp, int start)
{
	char	*env_var;
	int		env_len;
	// char	*tmp_var;
	int		remainder;
	int		len;

	env_var = get_env_var(node->value + start, envp);
	env_len = 0;
	if (env_var != NULL)
		env_len = ft_strlen(env_var);
	remainder = ft_strlen(node->value + start + ft_strlen(node->value + get_var_len(node->value, start)));
	len = (start - 1) + env_len + remainder;
	// tmp_var = malloc(sizeof(char) * (len + 1));
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

	head = tokenizer("ok$USE'R'ok");
	expansion(head, envp);
}
