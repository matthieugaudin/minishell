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
	*line = res;
}

static char	*expand_hdoc(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !is_space(line[i + 1])
			&& line[i + 1] != '\0' && is_posix_std(line[i + 1]))
		{
			expand_line(env, &line, i + 1);
			i = -1;
		}
		i++;
	}
	return (line);
}

static void	fill_here_doc(t_hdoc *hdoc, t_env *env, int here_doc)
{
	char	*line;
	char	*new;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, hdoc->limiter) == 0)
			break ;
		if (hdoc->expand)
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
	t_hdoc	*here_doc;

    while (cmds)
    {
        file_path = get_file_path();
		while (access(file_path, F_OK) == 0)
		{
			free(file_path);
			file_path = get_file_path();
		}
		here_doc = cmds->here_doc;
		while (here_doc)
		{
			if (cmds->fd_in != 0)
				close(cmds->fd_in);
			cmds->fd_in = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fill_here_doc(here_doc, env, cmds->fd_in);
			here_doc = here_doc->next;
		}
        cmds = cmds->next;
    }
}
