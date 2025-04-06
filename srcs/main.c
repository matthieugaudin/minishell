#include "../includes/execution.h"

int sigint_flag = 0;

t_data	*init_data(char **envp)
{
	t_data	*data;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	data = malloc(sizeof(t_data));
	data->env = create_env(envp);
	data->exp = create_export(data->env);
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
	t_token *token;

	if (!only_spaces(line))
	{
		token = tokenize_line(line);
		if (token && parse_tokens(token))
		{
			expand_tokens(token, data->env);
			remove_quotes(token);
			data->cmds = create_cmd(token);
			free_tokens(token, false);
			create_pipes(data, data->cmds);
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
