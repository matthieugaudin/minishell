#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	execute_cmd(t_data *data, t_cmd *cmd)
{
	char **envp;

	envp = convert_env_to_envp(data->env);
	if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(data, &cmd->args[1], true);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(data->env, &cmd->args[0], true);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(data, cmd->args[1], true);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(true);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd->args, true);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(data, cmd->args, true);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(data,  &cmd->args[1], -1, -1, true);
	else
		execve(cmd->path, cmd->args, envp);
}

void	close_hdoc_fds(t_cmd *cmds, bool is_child, int index)
{
	while (cmds)
	{
		if (cmds->fd_in != 0 && (cmds->index != index || !is_child))
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}

void	handle_builtins(t_data *data, t_cmd *cmd)
{
	int	stdin_tmp;
	int	stdout_tmp;

	stdin_tmp = dup(0);
	stdout_tmp = dup(1);
	open_here_doc(cmd, data->env);
	open_files(data, cmd, cmd->files);
	redirect_fds(data, cmd);
	if (sigint_flag != 1)
	{
		if (!ft_strcmp(cmd->args[0], "export"))
			ft_export(data, &cmd->args[1], false);
		else if (!ft_strcmp(cmd->args[0], "env"))
			ft_env(data->env, &cmd->args[0], false);
		else if (!ft_strcmp(cmd->args[0], "cd"))
			ft_cd(data, cmd->args[1], false);
		else if (!ft_strcmp(cmd->args[0], "pwd"))
			ft_pwd(false);
		else if (!ft_strcmp(cmd->args[0], "echo"))
			ft_echo(cmd->args, false);
		else if (!ft_strcmp(cmd->args[0], "unset"))
			ft_unset(data, cmd->args, false);
		else if (!ft_strcmp(cmd->args[0], "exit"))
			ft_exit(data, &cmd->args[1], stdin_tmp, stdout_tmp, false);
	}
	dup2(stdin_tmp, 0);
	dup2(stdout_tmp, 1);
	close(stdin_tmp);
	close(stdout_tmp);
}

bool	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (true);
	else if (!ft_strcmp(str, "echo"))
		return (true);
	else if (!ft_strcmp(str, "env"))
		return (true);
	else if (!ft_strcmp(str, "exit"))
		return (true);
	else if (!ft_strcmp(str, "export"))
		return (true);
	else if (!ft_strcmp(str, "pwd"))
		return (true);
	else if (!ft_strcmp(str, "unset"))
		return (true);
	else
		return (false);
}

void	execute_cmds(t_data *data, t_cmd *cmds)
{
	pid_t	pid;
	pid_t	last_pid;

	last_pid = -1;
	open_here_doc(cmds, data->env);
	while (cmds && sigint_flag != 1)
	{
		pid = fork();
		handle_signals(2);
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
		{
			close_hdoc_fds(data->cmds, true, cmds->index);
			open_files(data, cmds, cmds->files);
			if (cmds->args[0])
			{
				if (!is_builtin(cmds->args[0]))
					set_exec_path(data, cmds);
				redirect_fds(data, cmds);
				execute_cmd(data, cmds);
			}
		}
		if (cmds->index > 0)
			close(data->pipes[cmds->index - 1][0]);
		if (cmds->next)
			close(data->pipes[cmds->index][1]);
		cmds = cmds->next;
	}
	close_hdoc_fds(data->cmds, false, 0);
	wait_children(data, last_pid);
}
