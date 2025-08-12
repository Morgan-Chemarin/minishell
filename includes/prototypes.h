#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// ** BUILTINS **

int		ft_echo(t_cmd *cmd);
int		ft_env(t_env *envp);
int		ft_cd(t_cmd *cmd, t_env **env);
void	ft_exit(t_cmd *cmd, t_token *token, t_env *env, char *line);
int		ft_unset(t_env **env, t_cmd *cmd);
int		ft_pwd(void);

// export
void	ft_env_export(t_env *envp);
int		ft_export(t_cmd *cmd, t_env **env);

// utils_builtins
int		count_arg(char **arg);

// ** ENV **

// env_expansion.c
char	*expand_variables(char *str, t_env *env);
char	*get_env_value(char *name, t_env *env);

// init_env.c
t_env	*envp_to_list(char **envp);

// env_array.c
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
char	**env_list_to_array(t_env *env);
void	ft_free_split(char **arr);

// ** EXEC **

// exec_cmd.c
void	exec_cmd(t_cmd *cmd, t_env *env, t_token *token, char *line);

// pipe_cmd.c
t_cmd	*new_cmd(void);
int		count_args(t_token *token);

// heredoc.c
int		handle_heredoc(t_cmd *cmd, t_env *env);

// execve_utils.c
char	*get_path(char *cmd, t_env *env);
void	check_access_exec(char *cmd, char **args, char **envp);

// redir.c
void	handle_redirections(t_cmd *cmd);

// ** PARSER **

// parsing.c
t_cmd	*parser(t_token *tokens);
t_token	*create_struct_tokens(char **split);

// split_quote.c
char	**split_with_quote(char *line, t_env *env);
char	*extract_word(char *line, int *i, t_env *env, int skip_expand);

// split_quote_helper.c
char	*extract_quoted(char *line, int *i, int skip_expand, t_env *env);
int		count_tokens(char *line);

// split_utils.c
void	skip_spaces(char *line, int *i);
int		is_single_operator(char c);
int		is_double_operator(char *s, const char *op, int *i);
char	*extract_delimiter(char *line, int *i);

// token_builder.c

// ** UTILS **

// check_error.c
int		check_syntax_errors(t_token *tokens);

//free_utils
void    free_array_str(char    **str);
void    free_cmd(t_cmd *cmd);
void    free_token(t_token *token);
void    free_env(t_env *env);
void    free_export_add_env(t_env *new, char **arg);
void    free_all(t_cmd *cmd, t_token *token, t_env *env, char *line);

#endif