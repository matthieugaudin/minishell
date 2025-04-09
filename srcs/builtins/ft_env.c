/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:30:55 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:30:56 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_env(t_data *data, t_env *env, char **args, bool exit)
{
	if (args && args[1])
	{
		ft_putstr_fd("minishell: env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (value(data, 127, exit));
	}
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=", 1);
		if (env->value)
			ft_putendl_fd(env->value, 1);
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (value(data, 0, exit));
}
