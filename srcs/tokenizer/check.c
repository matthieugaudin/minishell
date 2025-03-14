#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

/*
Check if there are unexpected tokens because some caracters are sticked together
*/
char	check_line(char *str, char *set)
{
	int	i;
	int	nb_car;

	while (*set)
	{
		i = 0;
		nb_car = 0;
		while (str[i])
		{
			if (!in_quotes(str, i) && str[i] == *set)
				nb_car++;
			else if (!in_quotes(str, i) && nb_car > 0 && str[i] != *set)
				nb_car = 0;
			if (((*set == '<' || *set == '>') && nb_car > 2)
				|| (*set == '|' && nb_car > 1)
				|| (*set == '&' && nb_car > 0))
				return (*set);
			i++;
		}
		set++;
	}
	return ('\0');
}

/*
Check if the line entered has closed quotes in the good sequence.
*/
char	check_quotes(char *str)
{
	bool	quotes_open;
	char	quote;
	int		i;

	i = 0;
	quotes_open = false;
	while (str[i])
	{
		if (!quotes_open && (str[i] == '\'' || str[i] == '\"'))
		{
			quotes_open = true;
			quote = str[i];
		}
		else if (quotes_open && str[i] == quote)
		{
			quotes_open = false;
		}
		i++;
	}
	if (quotes_open)
		return (quote);
	else
		return ('\0');
}

void	syntax_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexepected token '", 2);
	write(2, &c, 1);
	ft_putstr_fd("'\n", 2);
	exit(2);
}
