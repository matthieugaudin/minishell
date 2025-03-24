#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct  s_file
{
    char            *name;
    enum e_token     type;
    struct s_file   *next;
}   t_file;

typedef struct  s_hdoc
{
    char            *limiter;
    bool            expand;
    struct s_hdoc   *next;
}   t_hdoc;

typedef struct s_cmd
{
    char			**args;
    char            *path;
    bool			is_here_doc;
	t_hdoc			*here_doc;
    t_file			*files;
    int             fd_in;
    int             fd_out;
    struct s_cmd	*next;
}	t_cmd;

/*==============PARSER==============*/
void    parse_tokens(t_token *token);
void	expand_tokens(t_token *node, t_env *env);
void	remove_quotes(t_token *tokens);
char	*get_env_name(char *envp_str);

/*==========EXEC DATA==========*/
t_cmd	*create_cmd(t_token *tokens);
/*void	create_export(t_data *data)*/
/*void	create_env(t_data *data, char **envp)*/

/*============LINKED LISTS===========*/
t_hdoc  *new_hdoc(char *limiter, bool is_quoted);
void	add_hdoc_back(t_hdoc **head, t_hdoc *new);
t_file	*new_file(char *name, enum e_token type);
void	add_file_back(t_file **head, t_file *new);

#endif /* PARSER_H */