/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:54:43 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/03 13:27:17 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*head;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("\'");
	while (1)
	{
		rl_outstream = stderr;
		line = readline("minishell>");
		if (line)
			add_history(line);
		head = tokenizer(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
