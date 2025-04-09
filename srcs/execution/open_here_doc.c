/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:38 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	handle_hdoc_file(t_data *data, t_file *files,
	t_cmd *cmds)
{
	char	*file_path;
	int		fd;

	if (files->type == HERE_DOC)
	{
		file_path = get_file_path();
		if (!file_path)
			free_all(data, EXIT_FAILURE);
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			free_all(data, EXIT_FAILURE);
		fill_here_doc(data, files, fd);
		if (is_last_redir(files))
		{
			cmds->fd_in = open(file_path, O_RDONLY);
			if (cmds->fd_in == -1)
				free_all(data, EXIT_FAILURE);
		}
		close(fd);
		unlink(file_path);
		free(file_path);
	}
}

void	open_here_doc(t_data *data, t_cmd *cmds)
{
	t_file	*files;

	g_sigint_flag = 0;
	while (cmds)
	{
		files = cmds->files;
		while (files)
		{
			handle_hdoc_file(data, files, cmds);
			files = files->next;
		}
		cmds = cmds->next;
	}
}
