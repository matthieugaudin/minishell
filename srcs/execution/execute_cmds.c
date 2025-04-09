#include "../../includes/builtins.h"

static void	ft_execve(t_data *data, t_cmd *cmd)
{
	char	**envp;

	envp = convert_env_to_envp(data, data->env);
	if (!envp)
		free_all(data, EXIT_FAILURE);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		free_envp(envp);
		free_all(data, EXIT_FAILURE);
	}
}

static void	execute_cmd(t_data *data, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(data, &cmd->args[1], true);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(data, data->env, &cmd->args[0], true);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(data, &cmd->args[1], true);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(data, true);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(data, cmd->args, true);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(data, cmd->args, true);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(data, &cmd->args[1], -1, -1, true);
	else
		ft_execve(data, cmd);
}

static void	handle_child_proc(t_data *data, t_cmd *cmds)
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
	free_all(data, exit_code(0, false));
}

void	execute_cmds(t_data *data, t_cmd *cmds)
{
	pid_t	pid;
	pid_t	last_pid;

	last_pid = -1;
	open_here_doc(data, cmds);
	while (cmds && g_sigint_flag != 1)
	{
		pid = s_fork(data);
		handle_signals(2);
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
			handle_child_proc(data, cmds);
		if (cmds->index > 0)
			close(data->pipes[cmds->index - 1][0]);
		if (cmds->next)
			close(data->pipes[cmds->index][1]);
		cmds = cmds->next;
	}
	close_hdoc_fds(data->cmds, false, 0);
	if (g_sigint_flag == 1)
		close_pipes(data->cmds, data->pipes);
	wait_children(data, last_pid);
}
