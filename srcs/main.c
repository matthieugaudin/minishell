#include "../includes/execution.h"

int sigint_flag = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "^C", 2);
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	hdoc_sigint(int sig)
{
	(void)sig;
	sigint_flag = 1;
	write(1, "^C", 2);
	close(0);
}

void	child_signals(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit", 4);
	write(1, "\n", 1);
}

void	handle_signals(int mode)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
	{
		sa.sa_handler = &handle_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 1)
	{
		sa.sa_handler = &hdoc_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == 2)
	{
		sa.sa_handler = &child_signals;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_token *token;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	data = malloc(sizeof(t_data));
	data->env = create_env(envp);
	data->exp = create_export(data->env);
	while (true)
	{
		handle_signals(0);
		rl_outstream = stderr;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			// free data
			exit(0);
		}
		if (!only_spaces(line))
		{
			token = tokenize_line(line);
			if (token && parse_tokens(token))
			{
				expand_tokens(token, data->env);
				remove_quotes(token);
				data->cmds = create_cmd(token);
				create_pipes(data, data->cmds);
				if (data->cmds->index == 0 && !data->cmds->next && is_builtin(data->cmds->args[0]))
					handle_builtins(data, data->cmds);
				else
					execute_cmds(data, data->cmds, envp);
				free_tokens(token, false);
				free_data(data);
			}
			add_history(line);
		}
	}
	rl_clear_history();
	free(data);
	// free_env_exp(&data->env, &data->exp);
	return (0);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_data	*data;

// 	(void)ac;
// 	(void)av;
// 	data = malloc(sizeof(t_data));
// 	data->env = create_env(envp);
// 	data->exp = create_export(data->env);
// 	free_env_exp(&data->env, &data->exp);
// 	free(data);
// }
