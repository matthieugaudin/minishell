/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_dbl_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:46 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:47 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

bool	in_dbl_quotes(char *str, int j)
{
	int		i;
	bool	quotes_open;
	bool	in_simple;

	i = 0;
	in_simple = false;
	quotes_open = false;
	while (i < j)
	{
		if (str[i] == '\'')
			in_simple = !in_simple;
		else if (str[i] == '\"' && !in_simple)
			quotes_open = !quotes_open;
		i++;
	}
	return (quotes_open);
}
