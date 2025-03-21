#include "../../includes/execution.h"
#include "../../includes/tokenizer.h"

/*
Check in a caracter is inside quotes, so we know the way we have to treat it.
*/
bool	in_quotes(char *str, int j)
{
	bool	quotes_open;
	char	quote;
	int		i;

	i = 0;
	quotes_open = false;
	while (i < j)
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
	return (quotes_open);
}

bool	in_dbl_quotes(char *str, int j)
{
	int		i;
	bool	quotes_open;

	i = 0;
	quotes_open = false;
	while (i < j)
	{
		if (str[i] == '\"')
			quotes_open = !quotes_open;
		i++;
	}
	return (quotes_open);
}
