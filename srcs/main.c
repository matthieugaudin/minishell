#include "../includes/execution.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_token *token;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->env = create_env(envp);
	data->exp = create_export(data->env);
	while (true)
	{
		rl_outstream = stderr;
		line = readline("minishell> ");
		if (line[0])
		{
			token = tokenize_line(line);
			parse_tokens(token);
			expand_tokens(token, data->env);
			remove_quotes(token);
			data->cmds = create_cmd(token);
			create_pipes(data, data->cmds);
			execute_cmds(data, data->cmds, envp);
			free_tokens(token, false);
			free_data(data);
			add_history(line);
		}
	}
	rl_clear_history();
	free(data);
	return (0);
}
