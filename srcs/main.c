#include "../includes/execution.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

bool	only_spaces(char *line)
{
	while (*line)
	{
		if (!is_space(*line))
			return (false);
		line++;
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_token *token;

	(void)argc;
	(void)argv;
	handle_signals();
	data = malloc(sizeof(t_data));
	data->env = create_env(envp);
	data->exp = create_export(data->env);
	while (true)
	{
		rl_outstream = stderr;
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			// free data
			exit(0);
		}
		if (!only_spaces(line))
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
