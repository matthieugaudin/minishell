/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:26 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:27 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	hdoc_warning(t_data *data, char *limiter, int line)
{
	char	*str_line;

	str_line = ft_itoa(line);
	if (!str_line)
		free_all(data, EXIT_FAILURE);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(str_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(str_line);
}

static void	handle_null_line(t_data *data, t_file *file, int fd, int i)
{
	s_dup2(data, fd, 0);
	close(fd);
	if (g_sigint_flag == 0)
		hdoc_warning(data, file->name, i);
	else if (g_sigint_flag == 1)
		exit_code(130, true);
}

static char	*expand_hdoc(t_data *data, t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
				expand_exit(data, &line, i + 1);
			else if (ft_isdigit(line[i + 1]))
				expand_digit(data, &line, i + 1);
			else if (is_posix_std(line[i + 1]))
				expand_line(data, env, &line, i + 1);
			else
			{
				i++;
				continue ;
			}
			i = -1;
		}
		i++;
	}
	return (line);
}

static void	handle_line(t_data *data, t_file *file, char *line, int here_doc)
{
	char		*new;

	if (file->expand)
	{
		new = expand_hdoc(data, data->env, line);
		write(here_doc, new, ft_strlen(new));
		free(new);
	}
	else
		write(here_doc, line, ft_strlen(line));
	write(here_doc, "\n", 1);
}

void	fill_here_doc(t_data *data, t_file *file, int here_doc)
{
	char		*line;
	int			fd;
	static int	i;

	fd = s_dup(data, 0);
	handle_signals(1);
	while (g_sigint_flag == 0)
	{
		line = readline("> ");
		i++;
		if (!line)
		{
			handle_null_line(data, file, fd, i);
			break ;
		}
		if (ft_strcmp(line, file->name) == 0)
			break ;
		handle_line(data, file, line, here_doc);
	}
	close(fd);
}
