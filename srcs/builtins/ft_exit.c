/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:30:58 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:30:59 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static bool	threshold_exceeded(char *str, long long res, int sign, int i)
{
	if (((-res == (LLONG_MIN / 10) && str[i] > '8')
			|| (-res < (LLONG_MIN / 10) && str[i]))
		|| (sign != -1 && ((res == (LLONG_MAX / 10)
					&& str[i] > '7') || (res > (LLONG_MAX / 10) && str[i]))))
		return (true);
	else
		return (false);
}

static bool	is_overflow(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (threshold_exceeded(str, res, sign, i))
			return (true);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (false);
}

static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !((str[i] == '+'
					|| str[i] == '-') && isdigit(str[i + 1])))
			return (false);
		i++;
	}
	if (is_overflow(str))
		return (false);
	return (true);
}

static void	handle_numeric(t_data *data, char **args, bool to_exit)
{
	if (!to_exit)
		ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_all(data, 2);
}

static void	handle_too_many(t_data *data, bool to_exit)
{
	if (!to_exit)
		ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	if (to_exit)
		free_all(data, 1);
	exit_code(1, true);
}

void	ft_exit(t_data *data, char **args, bool to_exit)
{
	int	code;

	if (!args[0])
	{
		if (!to_exit)
			ft_putendl_fd("exit", 1);
		free_all(data, exit_code(0, false));
	}
	else if (!is_numeric(args[0]))
		handle_numeric(data, args, to_exit);
	else if (args[1])
		handle_too_many(data, to_exit);
	else
	{
		code = ft_atoi(args[0]);
		if (!to_exit)
			ft_putendl_fd("exit", 1);
		free_all(data, code);
	}
}
