#include "../../includes/execution.h"

static char    *get_file_path(void)
{
	char 	alnum[63];
	char	file_path[5 + 20 + 4 + 1];
	char	buffer[20];
	char	*res;
	int		fd;
	int 	i;

	ft_memcpy(file_path, "/tmp/", 5);
	ft_memcpy(alnum, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", sizeof(alnum) - 1);
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, buffer, 20);
	close(fd);
	i = 0;
	while (i < 20)
	{
		file_path[i + 5] = alnum[(unsigned char)buffer[i] % (sizeof(alnum) - 1)];
		i++;
	}
	ft_memcpy(file_path + i + 5, ".tmp", 5);
	res = ft_strdup(file_path);
	return (res);
}

static void	expand_line(t_env *env, char **line, int start)
{
	char	*var_value;
	char	*var_name;
	char	*res;
	int		value_len;
	int		name_len;
	int		remainder;
	int		len;

	var_name = get_env_name(*line + start);
	var_value = get_var_value(env, var_name);
	value_len = ft_strlen(var_value);
	name_len = ft_strlen(var_name);
	remainder = ft_strlen(*line + start + ft_strlen(var_name));
	len = (start - 1) + value_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(res, *line, start);
	if (var_value)
		ft_strlcat(res + start - 1, var_value, value_len + 1);
	ft_strlcat(res + start - 1 + value_len, *line + start + name_len, remainder + 1);
	free(*line);
	*line = res;
}

static void	expand_exit(char **line, int start)
{
	char	*res;
	char	*code;
	int		code_len;
	int		remainder;
	int		len;

	code = ft_itoa(exit_code(0, false));
	code_len = ft_strlen(code);
	remainder = ft_strlen(*line + start + 1);
	len = (start - 1) + code_len + remainder;
	res = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(res, *line, start);
	ft_strlcat(res + start - 1, code, code_len + 1);
	ft_strlcat(res + start - 1 + code_len, *line + start + 1, remainder + 1);
	free(*line);
	*line = res;
}

static void	expand_digit(char **line, int start)
{
	char	*res;
	int		remainder;
	int		len;

	len = ft_strlen(*line) - 2;
	remainder = ft_strlen(*line + start + 1);
	res = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(res, *line, start);
	ft_strlcat(res + start - 1, *line + start + 1, remainder + 1);
	free(*line);
	*line = res;
}

static char	*expand_hdoc(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
				expand_exit(&line, i + 1);
			else if (ft_isdigit(line[i + 1]))
				expand_digit(&line, i + 1);
			else if (is_posix_std(line[i + 1]))
				expand_line(env, &line, i + 1);
			i = -1;
		}
		i++;
	}
	return (line);
}

static void	hdoc_warning(char *limiter, int line)
{
	char *str_line;

	str_line = ft_itoa(line);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(str_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

static void	fill_here_doc(t_file *file, t_env *env, int here_doc)
{
	char		*line;
	char		*new;
	static int	i;

	int fd = dup(0);
	handle_signals(1);
	while (sigint_flag == 0)
	{
		line = readline("> ");
		i++;
		if (!line)
		{
			dup2(fd, 0);
			close(fd);
			if (sigint_flag == 0)
				hdoc_warning(file->name, i);
			break ;
		}
		if (ft_strcmp(line, file->name) == 0)
			break ;
		if (file->expand)
		{
			new = expand_hdoc(env, line);
			write(here_doc, new, ft_strlen(new));
		}
		else
		{
			write(here_doc, line, ft_strlen(line));
		}
		write(here_doc, "\n", 1);
	}
}

void    open_here_doc(t_cmd *cmds, t_env *env)
{
    char	*file_path;
	t_file	*files;
	int		fd;

	sigint_flag = 0;
    while (cmds)
    {
        file_path = get_file_path();
		while (access(file_path, F_OK) == 0)
		{
			free(file_path);
			file_path = get_file_path();
		}
		files = cmds->files;
		while (files)
		{
			if (files->type == HERE_DOC)
			{
				fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				fill_here_doc(files, env, fd);
				if (is_last_redir(files))
				{
					close(fd);
					cmds->fd_in = open(file_path, O_RDONLY);
				}
				else
				{
					close(fd);
					unlink(file_path);
				}
			}
			files = files->next;
		}
        cmds = cmds->next;
    }
}
