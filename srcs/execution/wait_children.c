/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:52 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:53 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	wait_children(t_data *data, pid_t last_pid)
{
	int		status;
	t_cmd	*cmds;

	cmds = data->cmds;
	while (cmds)
	{
		if (last_pid != -1 && wait(&status) == last_pid)
		{
			if (WIFEXITED(status))
				exit_code(WEXITSTATUS(status), true);
			else if (WIFSIGNALED(status))
				exit_code(128 + WTERMSIG(status), true);
		}
		cmds = cmds->next;
	}
}
