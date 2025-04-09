#include "../../includes/parser.h"

static void	fill_tkn_value(char *value, char *tmp)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	while (tmp[i])
	{
		if (!(!in_quotes(tmp, i)
				&& (tmp[i] == '\'' || tmp[i] == '\"'))
			&& !(in_quotes(tmp, i) && tmp[i] == quote))
		{
			value[j] = tmp[i];
			j++;
		}
		else
		{
			quote = tmp[i];
		}
		i++;
	}
}

static int	count_del_quotes(t_token *token)
{
	char	*str;
	char	quote;
	int		nb_del;
	int		i;

	i = 0;
	nb_del = 0;
	quote = '\0';
	str = token->value;
	while (str[i])
	{
		if (!in_quotes(str, i) && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			nb_del++;
		}
		else if (in_quotes(str, i) && str[i] == quote)
			nb_del++;
		i++;
	}
	return (nb_del);
}

void	remove_quotes(t_data *data, t_token *tokens)
{
	int		to_remove;
	int		value_len;
	char	*tmp;

	tmp = NULL;
	while (tokens)
	{
		to_remove = count_del_quotes(tokens);
		if (to_remove > 0)
		{
			value_len = ft_strlen(tokens->value);
			tmp = tokens->value;
			tokens->value = malloc(sizeof(char) * (value_len - to_remove + 1));
			if (!tokens->value)
				free_all(data, EXIT_FAILURE);
			tokens->value[value_len - to_remove] = '\0';
			fill_tkn_value(tokens->value, tmp);
			free(tmp);
		}
		tokens = tokens->next;
	}
}
