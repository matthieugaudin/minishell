#include "../../includes/tokenizer.h"

static bool	special_car(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

static void	extract_token(char **s, int *len, int *i)
{
	while (**s && is_space(**s))
	{
		(*s)++;
		(*i)++;
	}
	while (**s && (!is_space(**s) || (is_space(**s) && in_quotes(*s - *i, *i)))
		&& (!special_car(**s) || (special_car(**s) && in_quotes(*s - *i, *i))))
	{
		(*i)++;
		(*s)++;
		(*len)++;
	}
	if (*len == 0 && special_car(**s) && !in_quotes(*s - *i, *i))
	{
		(*i)++;
		(*s)++;
		(*len)++;
		if (special_car(**s) && **s == *(*s - 1)
			&& (**s == '<' || **s == '>'))
		{
			(*i)++;
			(*s)++;
			(*len)++;
		}
	}
}

static bool	create_tokens(char *s, t_token **head)
{
	char	*value;
	int		len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		extract_token(&s, &len, &i);
		if (*s || len > 0)
		{
			value = malloc((len + 1) * sizeof(char));
			if (!value)
			{
				free_tokens(*head, true);
				exit(1);
			}
			ft_strlcpy(value, s - len, len + 1);
			append_token_node(head, value);
		}
	}
	return (true);
}

t_token	*tokenize_line(char *s)
{
	t_token	*head;
	char	quote;
	char	line;

	head = NULL;
	quote = check_quotes(s);
	line = check_line(s, "<>&");
	if (quote != '\0')
	{
		syntax_error(head, quote);
		return (NULL);
	}
	else if (line != '\0')
	{
		syntax_error(head, line);
		return (NULL);
	}
	create_tokens(s, &head);
	return (head);
}
