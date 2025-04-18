/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:34 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:35 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	open_files(t_data *data, t_cmd *cmd, t_file *files)
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
		if (fd == -1)
		{
			send_error(files->name, errno);
			free_all(data, 1);
		}
		if (is_last_redir(files)
			&& (files->type == OUTPUT || files->type == APPEND))
			cmd->fd_out = fd;
		else if (is_last_redir(files) && files->type == INPUT)
			cmd->fd_in = fd;
		else if (files->type != HERE_DOC)
			close(fd);
		files = files->next;
	}
}
