#include "../includes/execution.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_token *token;
	t_token *tmp;

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
			printf("%s\n\n", line);
			tmp = token;
			while (token)
			{
				printf("%s %d\n", token->value, token->type);
				token = token->next;
			}
			free_tokens(tmp, false);
			add_history(line);
		}
	}
	rl_clear_history();
	return (0);
}
