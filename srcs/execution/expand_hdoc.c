/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:23 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:24 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static t_expand_data	create_expand_data(t_data *data,
	t_env *env, char *line, int start)
{
	t_expand_data	res;

	res.data = data;
	res.line = line;
	res.var_name = get_env_name(data, line + start);
	res.var_value = get_var_value(env, res.var_name);
	res.start = start;
	return (res);
}

int	get_total_len(t_expand_data exp)
{
	int		value_len;
	int		name_len;
	int		remainder;
	int		len;

	value_len = ft_strlen(exp.var_value);
	name_len = ft_strlen(exp.var_name);
	remainder = ft_strlen(exp.line + exp.start + name_len);
	len = (exp.start - 1) + value_len + remainder;
	return (len);
}

void	expand_line(t_data *data, t_env *env, char **line, int start)
{
	t_expand_data	exp;
	int				len;
	char			*res;
	int				value_len;
	int				remainder;

	exp = create_expand_data(data, env, *line, start);
	len = get_total_len(exp);
	value_len = ft_strlen(exp.var_value);
	remainder = ft_strlen(*line + start + ft_strlen(exp.var_name));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(exp.var_name);
		free_all(data, EXIT_FAILURE);
	}
	ft_strlcpy(res, *line, start);
	if (exp.var_value)
		ft_strlcat(res + start - 1, exp.var_value, value_len + 1);
	ft_strlcat(res + start - 1 + value_len, *line + start
		+ ft_strlen(exp.var_name), remainder + 1);
	free(*line);
	free(exp.var_name);
	*line = res;
}

void	expand_exit(t_data *data, char **line, int start)
{
	char	*res;
	char	*code;
	int		code_len;
	int		remainder;
	int		len;

	code = ft_itoa(exit_code(0, false));
	if (!code)
		free_all(data, EXIT_FAILURE);
	code_len = ft_strlen(code);
	remainder = ft_strlen(*line + start + 1);
	len = (start - 1) + code_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		free(code);
		free_all(data, EXIT_FAILURE);
	}
	ft_strlcpy(res, *line, start);
	ft_strlcat(res + start - 1, code, code_len + 1);
	ft_strlcat(res + start - 1 + code_len, *line + start + 1, remainder + 1);
	free(*line);
	*line = res;
}

void	expand_digit(t_data *data, char **line, int start)
{
	char	*res;
	int		remainder;
	int		len;

	len = ft_strlen(*line) - 2;
	remainder = ft_strlen(*line + start + 1);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		free_all(data, EXIT_FAILURE);
	ft_strlcpy(res, *line, start);
	ft_strlcat(res + start - 1, *line + start + 1, remainder + 1);
	free(*line);
	*line = res;
}
