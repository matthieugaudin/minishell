#include "../../includes/execution.h"

static void	fill_paths(t_data *data, t_cmd *cmd, char **paths, int i)
{
	char	*tmp;

	tmp = paths[i];
	paths[i] = malloc(sizeof(char) * (ft_strlen(paths[i])
				+ 1 + ft_strlen(cmd->args[0]) + 1));
	if (!paths[i])
	{
		while (--i)
			free(paths[i]);
		free_all(data, EXIT_FAILURE);
	}
	paths[i][ft_strlen(tmp) + 1 + ft_strlen(cmd->args[0])] = '\0';
	ft_strlcpy(paths[i], tmp, ft_strlen(tmp) + 1);
	ft_strlcat(paths[i] + ft_strlen(tmp), "/", 2);
	ft_strlcat(paths[i] + ft_strlen(tmp), cmd->args[0],
		ft_strlen(cmd->args[0]) + 2);
	free(tmp);
}

static char	**get_paths(t_data *data, t_cmd *cmd, t_env *env)
{
	char	**paths;
	int		i;

	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		free_all(data, EXIT_FAILURE);
	i = 0;
	while (paths[i])
	{
		fill_paths(data, cmd, paths, i);
		i++;
	}
	return (paths);
}

static char	*get_access_path(t_data *data, char **paths)
{
	char	*access_path;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
	i = 0;
	access_path = NULL;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			access_path = ft_strdup(paths[i]);
			if (!access_path)
				free_all(data, EXIT_FAILURE);
			return (access_path);
		}
		i++;
	}
	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
	return (access_path);
}

static void	special_cases(t_data *data, t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->args[0], __O_DIRECTORY);
	if (fd != -1)
	{
		send_error(cmd->args[0], EISDIR);
		close(fd);
		free_all(data, 126);
	}
	if (access(cmd->args[0], X_OK) == -1)
	{
		send_error(cmd->args[0], -1);
		if (errno == ENOTDIR || errno == EACCES)
			free_all(data, 126);
		free_all(data, 127);
	}
	cmd->path = cmd->args[0];
}

void	set_exec_path(t_data *data, t_cmd *cmd)
{
	char	**paths;

	if (!ft_strcmp(cmd->args[0], ""))
		cmd_not_found(data, cmd->args[0]);
	if (is_executable(cmd->args[0]) || cmd->args[0][0] == '/')
	{
		special_cases(data, cmd);
	}
	else
	{
		if (ft_strcmp(cmd->args[0], ".") && ft_strcmp(cmd->args[0], ".."))
		{
			paths = get_paths(data, cmd, data->env);
			cmd->path = get_access_path(data, paths);
		}
		if (!cmd->path)
			cmd_not_found(data, cmd->args[0]);
	}
}
