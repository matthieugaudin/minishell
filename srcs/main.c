#include "../includes/execution.h"

int sigint_flag = 0;

t_data	*init_data(char **envp)
{
	t_data	*data;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->env = NULL;
	data->exp = NULL;
	data->cmds = NULL;
	data->tokens = NULL;
	create_env(data, envp);
	create_export(data);
	return (data);
}

void	handle_shell_exit(t_data	*data)
{
	ft_putendl_fd("exit", 1);
	free_all(data, exit_code(0, false));
}

void	process_line(t_data	*data, char *line)
{

	if (!only_spaces(line))
	{
		data->tokens = tokenize_line(data, line);
		if (data->tokens && parse_tokens(data, data->tokens))
		{
			expand_tokens(data, data->tokens, data->env);
			remove_quotes(data, data->tokens);
			data->cmds = create_cmd(data, data->tokens);
			create_pipes(data, data->cmds);
			// HERE LAST FREE//
			if (data->cmds->index == 0 && !data->cmds->next && is_builtin(data->cmds->args[0]))
				handle_builtins(data, data->cmds);
			else
				execute_cmds(data, data->cmds);
			add_history(line);
		}
		free_all(data, -2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_data(envp);
	while (true)
	{
		handle_signals(0);
		data->line = readline("minishell> ");
		if (!data->line)
			handle_shell_exit(data);
		process_line(data, data->line);
	}
	free_all(data, 0);
}
