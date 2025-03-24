#include "../../includes/tokenizer.h"

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
