#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

void	check_unexpected(char *s)
{
	char	quote_tkn;
	char	line_tkn;

	quote_tkn = check_quotes(s);
	line_tkn = check_line(s, "<>|&");
	if (quote_tkn != '\0')
	{
		send_token_err(quote_tkn);
		exit (2);
	}
	else if (line_tkn != '\0')
	{
		send_token_err(line_tkn);
		exit (2);
	}
}

bool	special_car(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

void	extract_token(char **s, int *len, int *i)
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

bool	create_tokens(char *s, t_token **head)
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
			ft_strlcat(value, s - len, len + 1);
			append_token_node(head, value);
		}
	}
	return (true);
}

t_token	*tokenizer(char *s)
{
	t_token	*head;

	head = NULL;
	check_unexpected(s);
	create_tokens(s, &head);
	return (head);
}
