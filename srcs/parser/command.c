#include "../../includes/minishell.h"
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
	t_list	*limiter;
	t_file	*file;

	file = NULL;
	limiter = NULL;
	if (tokens->prev->type == HERE_DOC)
	{
		cmd->is_here_doc = true;
		limiter = ft_lstnew(tokens->value);
		ft_lstadd_back(&cmd->here_doc, limiter);
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
// 	t_list	*here_doc;
// 	t_file	*file;
// 	int		i = 0;

// 	line = "<out\"\"file";
// 	printf("%s\n\n", line);
// 	tokens = tokenizer(line);
// 	expansion(tokens, create_env(envp));
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
//             printf("  - %s\n", (char *)here_doc->content);
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
