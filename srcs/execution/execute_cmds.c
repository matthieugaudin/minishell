#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	execute_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	// convert envp to char **
	if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(data, cmd->args, true);
	if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(data->env, &cmd->args[0], true);
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(data, cmd->args[1], true);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(true);
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd->args, true);
	if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(data, cmd->args, true);
	if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit();
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
	open_here_doc(cmd, data->env);
	if (sigint_flag != 1)
	{
		if (!ft_strcmp(cmd->args[0], "export"))
			ft_export(data, &cmd->args[1], false);
		if (!ft_strcmp(cmd->args[0], "env"))
			ft_env(data->env, &cmd->args[0], false);
		if (!ft_strcmp(cmd->args[0], "cd"))
			ft_cd(data, cmd->args[1], false);
		if (!ft_strcmp(cmd->args[0], "pwd"))
			ft_pwd(false);
		if (!ft_strcmp(cmd->args[0], "echo"))
			ft_echo(cmd->args, false);
		if (!ft_strcmp(cmd->args[0], "unset"))
			ft_unset(data, cmd->args, false);
		if (!ft_strcmp(cmd->args[0], "exit"))
			ft_exit();
	}
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

void	execute_cmds(t_data *data, t_cmd *cmds, char **envp)
{
	pid_t	pid;
	pid_t	last_pid;

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
			open_files(cmds, cmds->files);
			if (cmds->args[0] != NULL)
			{
				if (!is_builtin(cmds->args[0]))
					set_exec_path(data, cmds);
				redirect_fds(data, cmds);
				execute_cmd(data, cmds, envp);
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
