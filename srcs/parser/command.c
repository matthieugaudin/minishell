#include "../../includes/execution.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"

void	set_last_cmd_next(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*last_cmd;

	if (*cmds == NULL)
	{
		*cmds = cmd;
		return ;
	}
	else
	{
		last_cmd = *cmds;
		while (last_cmd->next)
		{
			last_cmd = last_cmd->next;
		}
		last_cmd->next = cmd;
	}
}

void	handle_files(t_token *tokens, t_cmd *cmd)
{
	t_hdoc	*limiter;
	t_file	*file;

	file = NULL;
	limiter = NULL;
	if (tokens->prev->type == HERE_DOC)
	{
		cmd->is_here_doc = true;
		limiter = new_hdoc(tokens->value, tokens->hdoc_quoted);
		add_hdoc_back(&cmd->here_doc, limiter);
	}
	else
	{
		file = new_file(tokens->value, tokens->prev->type);
		add_file_back(&cmd->files, file);
	}
}

void	set_cmd_content(t_token **tokens, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == FILE_T)
		{
			handle_files(*tokens, cmd);
		}
		else if ((*tokens)->type == COMMAND)
		{
			cmd->args[i] = (*tokens)->value;
			i++;
		}
		*tokens = (*tokens)->next;
	}
}

void	init_cmd_content(t_cmd *cmd, t_token *tokens)
{
	int	nb_cmds;

	nb_cmds = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			nb_cmds++;
		tokens = tokens->next;
	}
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->fd_out = 1;
	cmd->args = malloc(sizeof(char *) * (nb_cmds + 1));
	cmd->args[nb_cmds] = NULL;
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;

	cmd = NULL;
	cmds = NULL;
	while (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		init_cmd_content(cmd, tokens);
		set_cmd_content(&tokens, cmd);
		set_last_cmd_next(&cmds, cmd);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char	*line;
// 	t_token	*tokens;
// 	t_cmd	*cmd;
// 	t_hdoc	*here_doc;
// 	t_file	*file;
// 	t_data	*data = malloc(sizeof(t_data));
// 	int		i = 0;

// 	line = "\"BONJOUR\"$\"\"";
// 	printf("%s\n\n", line);
// 	tokens = tokenizer(line);
// 	create_env(data, envp);
// 	expansion(tokens, data->env);
// 	remove_quotes(tokens);
// 	cmd = create_cmd(tokens);
//     while (cmd)
//     {
//         printf("=== Command Node ===\n");

//         // Print args
//         printf("Arguments: ");
//         if (cmd->args)
//         {
//             for (i = 0; cmd->args[i]; i++)
//                 printf("%s ", cmd->args[i]);
//         }
//         printf("\n");

//         // Print is_here_doc
//         printf("Here-Doc: %s\n", cmd->is_here_doc ? "true" : "false");

//         // Print here_doc
//         printf("Here-Doc Content:\n");
//         here_doc = cmd->here_doc;
//         while (here_doc)
//         {
//             printf("  - %s\n", (char *)here_doc->limiter);
//             here_doc = here_doc->next;
//         }

//         // Print files
//         printf("Files:\n");
//         file = cmd->files;
//         while (file)
//         {
//             printf("  - Name: %s, Type: %u\n", file->name, file->type);
//             file = file->next;
//         }

//         printf("\n");

//         // Move to next command node
//         cmd = cmd->next;
//     }
// }
