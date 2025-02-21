/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:54:43 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/21 18:27:38 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	test_tokenizer(t_token *head)
{
	t_token	*node;

	node = head;
	while (node)
	{
		printf("value : %s type : %d", node->value, node->type);
		node = node->next;
	}
}

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
		line = readline("$>");
		if (line)
			add_history(line);
		head = tokenizer(line);
		test_tokenizer(head);
		free(line);
	}
	rl_clear_history();
	return (0);
}
