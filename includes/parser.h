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
char	*get_var_value(t_env *env, char *var_name);
char	*get_env_name(char *envp_str);
void	free_env_node(t_env *node);
void	ft_update_env_node(t_env **env, t_env *new_node);
void	ft_update_exp_node(t_env **exp, t_env *new_node);
t_env	*ft_new_node(char *name, char *value);

/*==========EXEC DATA==========*/
t_cmd	*create_cmd(t_token *tokens);
t_env	*create_export(t_env *env);
t_env	*create_env(char **envp);

/*============LINKED LISTS===========*/
t_hdoc  *new_hdoc(char *limiter, bool is_quoted);
void	add_hdoc_back(t_hdoc **head, t_hdoc *new);
t_file	*new_file(char *name, enum e_token type);
void	add_file_back(t_file **head, t_file *new);

#endif /* PARSER_H */