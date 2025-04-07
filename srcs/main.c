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
		free_all(data);
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
	free_env_exp(&data->env, &data->exp);
	free(data);
	exit(exit_code(0, false));
}

void	process_line(t_data	*data, char *line)
{

	if (!only_spaces(line))
	{
		data->tokens = tokenize_line(data, line);
		if (data->tokens && parse_tokens(data->tokens))
		{
			expand_tokens(data, data->tokens, data->env);
			remove_quotes(data, data->tokens);
			data->cmds = create_cmd(data, data->tokens);
			free_tokens(data->tokens, false);
			create_pipes(data, data->cmds);
			// HERE LAST FREE//
			if (data->cmds->index == 0 && !data->cmds->next && is_builtin(data->cmds->args[0]))
				handle_builtins(data, data->cmds);
			else
				execute_cmds(data, data->cmds);
			free_data(data);
		}
		add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;

	(void)argc;
	(void)argv;
	data = init_data(envp);
	while (true)
	{
		handle_signals(0);
		line = readline("minishell> ");
		if (!line)
			handle_shell_exit(data);
		process_line(data, line);
	}
	rl_clear_history();
	free_env_exp(&data->env, &data->exp);
	free(data);
	return (0);
}
