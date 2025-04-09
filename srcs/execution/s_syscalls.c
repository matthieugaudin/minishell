/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_syscalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:42 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:43 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	s_dup2(t_data *data, int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		free_all(data, EXIT_FAILURE);
}

int	s_dup(t_data *data, int fd)
{
	int	fd_cpy;

	fd_cpy = dup(fd);
	if (fd_cpy == -1)
		free_all(data, EXIT_FAILURE);
	return (fd_cpy);
}

int	s_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		while (wait(NULL) > 0)
			;
		free_all(data, EXIT_FAILURE);
	}
	return (pid);
}
