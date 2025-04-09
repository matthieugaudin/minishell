/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_digit_tkn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:07 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:08 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	expand_digit_tkn(t_data *data, t_token *node, int start)
{
	char	*res;
	int		remainder;
	int		len;

	len = ft_strlen(node->value) - 2;
	remainder = ft_strlen(node->value + start + 1);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		free_all(data, EXIT_FAILURE);
	ft_strlcpy(res, node->value, start);
	ft_strlcat(res + start - 1, node->value + start + 1, remainder + 1);
	free(node->value);
	node->value = res;
}
