#include "../../includes/execution.h"
#include "../../includes/parser.h"

void	send_error(char *arg, int errno_cpy)
{
	if (errno_cpy != -1)
		errno = errno_cpy;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	cmd_not_found(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": command not found", 2);
}

char	**get_paths(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;
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
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = malloc(sizeof(char) * (ft_strlen(paths[i]) + 1 + ft_strlen(cmd->args[0]) + 1));
		paths[i][ft_strlen(paths[i]) + 1 + ft_strlen(cmd->args[0])] = '\0';
		ft_memcpy(paths[i], tmp, ft_strlen(tmp));
		ft_memcpy(paths[i] + ft_strlen(paths[i]), "/", 1);
		ft_memcpy(paths[i] + ft_strlen(paths[i]), cmd->args[0], ft_strlen(cmd->args[0]));
		i++;
	}
	return (paths);
}

char	*get_access_path(char **paths)
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
			return (access_path);
		}
		i++;
	}
	return (access_path);
}

void	special_cases(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->args[0], __O_DIRECTORY);
	if (fd != -1)
	{
		send_error(cmd->args[0], EISDIR);
		exit (126);
	}
	if (access(cmd->args[0], X_OK) == -1)
	{
		send_error(cmd->args[0], -1);
		if (errno == ENOTDIR || errno == EACCES)
			exit (126);
		exit (127);
	}
	cmd->path = cmd->args[0];
}

void	find_exec_path(t_cmd *cmd, t_data *data)
{
	char 	**paths;
	int		fd;

    if (ft_strncmp(cmd->args[0], "./", 2) == 0 || cmd->args[0][0] == '/')
    {
		special_cases(cmd);
    }
    else
    {
        paths = get_paths(cmd, data->env);
        cmd->path = get_access_path(paths);
        if (!cmd->path)
		{
			cmd_not_found(cmd->args[0]);
			exit (127);
		}
    }
}

 /*
 int main(int argc, char **argv, char **envp)
 {
	 (void)argc;
	 (void)argv;
	 // (void)envp;
	 t_data *data = malloc(sizeof(t_data));
	 t_token *token = tokenizer("sfwfdsfasdfsok");
	 remove_quotes(token);
	 t_cmd *cmd = create_cmd(token);
	 create_env(data, envp);
	 find_exec_path(cmd, data);
	 printf("%s\n", cmd->path);
 }
 */
