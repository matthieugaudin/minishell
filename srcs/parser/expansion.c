/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:55:36 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/06 18:38:06 by mgaudin          ###   ########.fr       */
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
	char	*tmp_var;
	int		remainder;
	int		len;

	env_var = get_env_var(node->value + start, envp);
	if (env_var != NULL)
	{
		// replace with the envp var (allocate + strcat)
		remainder = node->value + start + get_var_len(node->value, start);
		len = start + ft_strlen(*env_var) + remainder;
		tmp_var = malloc(sizeof(char) * (len + 1));
		ft_strlcat(tmp_var, node->value, start);
		ft_strlcat(tmp_var, node->value + start, ft_strlen(*env_var));
		ft_strlcat(tmp_var, node->value + start + ft_strlen(*env_var), remainder);
	}
	// else
	// {
	// 	// replace with nothing
	// }
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

int main(int argc, char **argv, char **envp)
{
	t_token *head;

	(void)argc;
	(void)argv;

	head = tokenizer("$LSCOLORSS");
	expansion(head, envp);
}
