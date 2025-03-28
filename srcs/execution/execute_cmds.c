#include "../../includes/execution.h"

static void	execute_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	(void)data;
	// check for builtins
	// convert envp to char **
	execve(cmd->path, cmd->args, envp);
}

void	execute_cmds(t_data *data, t_cmd *cmds, char **envp)
{
	pid_t	pid;
	pid_t	last_pid;

	open_here_doc(cmds, data->env);
	while (cmds)
	{
		pid = fork();
		if (!cmds->next)
			last_pid = pid;
		if (pid == 0)
		{
			open_files(cmds, cmds->files);
			if (cmds != NULL)
			{
				set_exec_path(data, cmds);
				redirect_fds(data, cmds);
				execute_cmd(data, cmds, envp);
			}
		}
		cmds = cmds->next;
	}
	wait_children(data, last_pid);
}

// heredoc as infile doesn't work : <<l1 cat >out
// the bad file is displayed : <create_pipes.c <<lim cat
// "ls <<l1<<l2 | <<l3 ls <<l4<<l5 | <<l6 cat -e >out"
// ls >a| ls >>a | <<lim ls <<lim1 | <<lim2 ls
// ls >a| ls >>a | <<l1 ls | <<l2 ls
// ls >a| ls >>a | <<l1<<l2 ls |  ls


// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *line;

// 	t_data *data = malloc(sizeof(t_data));
// 	data->env = create_env(envp);
// 	data->exp = create_export(data->env);
// 	line = "ls | cat |ls > out";
// 	t_token *token = tokenize_line(line);
// 	parse_tokens(token);
// 	expand_tokens(token, data->env);
// 	remove_quotes(token);
// 	data->cmds = create_cmd(token);
// 	create_pipes(data, data->cmds);
// 	execute_cmds(data, data->cmds, envp);
// }
