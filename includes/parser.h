#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

/*==============PARSER==============*/
bool    parse_tokens(t_data *data, t_token *token);
void	expand_tokens(t_data *data, t_token *node, t_env *env);
void	remove_quotes(t_data *data, t_token *tokens);
char	*get_var_value(t_env *env, char *var_name);
char	*get_env_name(t_data *data, char *envp_str);
void	free_env_node(t_env *node);
void	ft_update_env_node(t_env **env, t_env *new_node);
void	ft_update_exp_node(t_env **exp, t_env *new_node);
void	change_head(t_env **head, t_env *new_node);
t_env	*ft_new_node(char *name, char *value);
char	**convert_env_to_envp(t_env *env);

/*==========EXEC DATA==========*/
t_cmd	*create_cmd(t_data *data, t_token *tokens);
void	create_export(t_data *data);
void	create_env(t_data *data, char **envp);

/*============LINKED LIST===========*/
t_file	*new_file(t_data *data, char *name, enum e_token type, bool hdoc_quotes);
void	add_file_back(t_file **head, t_file *new);

/*============UTILS===========*/
bool	is_last_redir(t_file *file);
bool	only_spaces(char *line);

#endif /* PARSER_H */