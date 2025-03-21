#include "../../includes/execution.h"
#include "../includes/tokenizer.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*head;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("\'");
	while (1)
	{
		rl_outstream = stderr;
		line = readline("minishell>");
		if (line)
			add_history(line);
		head = tokenizer(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
