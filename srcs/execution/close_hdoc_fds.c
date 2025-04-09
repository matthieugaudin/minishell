/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_hdoc_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:13 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:14 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	close_hdoc_fds(t_cmd *cmds, bool is_child, int index)
{
	while (cmds)
	{
		if (cmds->fd_in != 0 && (cmds->index != index || !is_child))
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}
