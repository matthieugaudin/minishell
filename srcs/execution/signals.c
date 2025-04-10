/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:50 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/10 12:06:44 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "^C", 2);
	write(1, "\n", 2);
	exit_code(130, true);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	hdoc_sigint(int sig)
{
	(void)sig;
	g_sigint_flag = 1;
	write(1, "^C", 2);
	close(0);
}

static void	child_signals(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit", 4);
	write(1, "\n", 1);
}

void	handle_signals(int mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
	{
		sa.sa_handler = &handle_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 1)
	{
		sa.sa_handler = &hdoc_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 2)
	{
		sa.sa_handler = &child_signals;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
