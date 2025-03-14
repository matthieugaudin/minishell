#include "../../includes/minishell.h"
#include "../../includes/parser.h"

// handle heredoc
// open every other files
// fork for every cmd
//      -> find the executable
//         if cmd not found it juste skip the redirection and exece
//      -> redirect fds
//      -> check if there is a builtin
//      -> exec command
//      -> wait for all processes

char    *random_file(void)
{
    char	*file_path;
	char	*file_name;
	int		name_len;
	int		total_len;
    int		fd;

	name_len = 15;
	file_name = malloc(sizeof(char) * (name_len + 1));
	file_name[name_len] = '\0';
	fd = open("/dev/urandom", O_RDONLY, 0644);
	if (read(fd, file_name, name_len) == -1)
	{
		perror("read system call failed");
	}
	total_len = ft_strlen("/tmp/") + name_len + ft_strlen(".tmp");
	file_path = malloc(sizeof(char) * (total_len + 1));
	ft_strlcpy(file_path, "/tmp/", 6);
	ft_strlcat(file_path + 5, file_name, name_len + 1);
	ft_strlcat(file_path + 5 + name_len, ".tmp", 5);
	close(fd);
	return (file_path);
}

void    handle_here_doc(t_cmd *cmds)
{
    char	*file_path;
	int		fd;

    while (cmds)
    {
        // creer un nom random et un path dans /tmp
        file_path = random_file();
		while (cmds->here_doc)
		{
            // ouvrir un fichier .tmp avec ce nom et flags destr
			fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            // lire stdin avec readline
			cmds->here_doc = cmds->here_doc->next;
		}
        cmds = cmds->next;
    }
}

void    execution(t_cmd *cmds)
{
    handle_here_doc(cmds);
}
