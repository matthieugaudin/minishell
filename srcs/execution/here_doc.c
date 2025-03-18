#include "../../includes/minishell.h"
#include "../../includes/parser.h"

char    *get_file_path(void)
{
	char	*buffer;
	char	*res;
	char 	alnum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int		fd;
	int 	i;

	buffer = malloc(sizeof(char) * 5 + 30 + 4);
	buffer[30] = '\0';
	res = malloc(sizeof(char) * (5 + 31 + 4));
	res[5 + 30 + 4] = '\0';
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, buffer + 5, 30);
	ft_strlcpy(res, "/tmp/", 6);
	i = 5;
	while (i < 30)
	{
		res[i] = alnum[(unsigned char)buffer[i] % (sizeof(alnum) - 1)];
		i++;
	}
	ft_strlcat(res + 5 + i - 5, ".tmp", 5);
	return (res);
}

void	fill_here_doc(t_cmd *cmds, int here_doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, cmds->here_doc->content) == 0)
			break ;
		write(here_doc, line, ft_strlen(line));
		write(here_doc, "\n", 1);
		free(line);
	}
	free(line);
}

void    open_here_doc(t_cmd *cmds)
{
    char	*file_path;

    while (cmds)
    {
        file_path = get_file_path();
		while (access(file_path, F_OK) == 0)
		{
			free(file_path);
			file_path = get_file_path();
		}
		while (cmds->here_doc)
		{
			cmds->fd_in = open(file_path, O_WRONLY | O_CREAT, 0644);
			fill_here_doc(cmds, cmds->fd_in);
			cmds->here_doc = cmds->here_doc->next;
		}
        cmds = cmds->next;
    }
}
