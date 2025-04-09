#include "../../includes/execution.h"

static void	fill_random_name(char *dst, char *buffer, const char *alnum)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		dst[i] = alnum[(unsigned char)buffer[i] % 62];
		i++;
	}
}

char	*get_file_path(void)
{
	char	*alnum;
	char	file_path[5 + 20 + 4 + 1];
	char	buffer[20];
	int		fd;

	ft_memcpy(file_path, "/tmp/", 5);
	alnum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, buffer, 20) == -1)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	fill_random_name(file_path + 5, buffer, alnum);
	ft_memcpy(file_path + 25, ".tmp", 5);
	return (ft_strdup(file_path));
}
