/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:34 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/11 12:30:44 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

bool	handle_error(t_data *data, t_file *files, int fd, bool parent)
{
	if (fd == -1)
	{
		send_error(files->name, errno);
		if (!parent)
			free_all(data, 1);
		exit_code(1, true);
		free_all(data, -2);
		return (false);
	}
	return (true);
}

bool	open_files(t_data *data, t_cmd *cmd, t_file *files, bool parent)
{
	int	fd;

	fd = 0;
	while (files)
	{
		if (files->type == INPUT)
			fd = open(files->name, O_RDONLY);
		else if (files->type == OUTPUT)
			fd = open(files->name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (files->type == APPEND)
			fd = open(files->name, O_RDWR | O_CREAT | O_APPEND, 0664);
		if (!handle_error(data, files, fd, parent))
			return (false);
		if (is_last_redir(files)
			&& (files->type == OUTPUT || files->type == APPEND))
			cmd->fd_out = fd;
		else if (is_last_redir(files) && files->type == INPUT)
			cmd->fd_in = fd;
		else if (files->type != HERE_DOC)
			close(fd);
		files = files->next;
	}
	return (true);
}
