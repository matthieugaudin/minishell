/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:54:43 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/19 11:36:33 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("$>");
		if (line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
