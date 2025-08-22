/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:34:08 by dev               #+#    #+#             */
/*   Updated: 2025/08/22 06:55:05 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// ** MAIN **

// main_loop.c
int		process_line(char *line, t_env *env);

// ** BUILTINS **

int		ft_echo(t_cmd *cmd);
int		ft_env(t_env *envp);
int		ft_cd(t_cmd *cmd, t_env **env);
void	ft_exit(t_cmd *cmd, t_all *all);
int		ft_unset(t_env **env, t_cmd *cmd);
int		ft_pwd(void);

// export
void	ft_env_export(t_env *envp);
int		ft_export(t_cmd *cmd, t_env **env);
void	add_env_node(t_env **env, t_env *new);

// utils_builtins
int		count_arg(char **arg);
int		is_valid_long_long(char *str);

// ** ENV **

// env_expansion.c
char	*expand_variables(char *str, t_env *env);
char	*get_env_value(char *name, t_env *env);

// init_env.c
t_env	*envp_to_list(char **envp);

// env_array.c
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
char	**env_list_to_array(t_env *env);

// ** EXEC **

// exec_cmd.c
void	exec_cmd(t_cmd *cmd, t_env *env, t_token *token, char *line);
void	execute_parent_process(pid_t pid, t_cmd *cmd, int fds[3]);
void	execute_child_process(t_cmd *cmd, t_all *all, t_exec_data *data);

// pipe_cmd.c
t_cmd	*new_cmd(void);
int		count_args(t_token *token);
void	dot_command(t_cmd *cmd, t_env *env, t_all *all);

// heredoc.c
int		handle_heredoc(t_cmd *cmd, t_env *env);

// execve_utils.c
char	*get_path(char *cmd, t_env *env);
void	check_access_exec(char *cmd, char **args, char **envp);

// exec_cmd_utils.c
void	check_access(char *path, char **args, char **envp);
void	restore_fds(int saved_fds[2]);
void	exec_cmd_loop(t_cmd *cmd, t_env **env, t_all *all);

// exec_cmd_utils_children.c
void	wait_all_children(pid_t last_pid);
void	setup_child_pipes(t_cmd *cmd, int in_fd, int pipe_fd[2]);
void	child_exit_handler(char *path, char **envp_arr, t_all *all);

// wait_pid_remastered.c
void	wait_pid_remastered(pid_t pid);

// redir.c
void	handle_redirections(t_cmd *cmd, t_all *all);

// exec_builtins.c
void	exec_builtin(t_cmd *cmd, t_env **env, t_all *all);
int		is_stateful_builtin(t_cmd *cmd);

// ** PARSER **

// parsing.c
t_cmd	*parser(t_token *tokens);

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
char	*handle_quotes(char *line, int *i, int skip_expand, t_env *env);

// tokens_redir.c
int		set_input(t_cmd *cmd, t_token **tokens);
int		set_output(t_cmd *cmd, t_token **tokens, int append);
int		set_heredoc(t_cmd *cmd, t_token **tokens);

// tokens.c
t_token	*create_struct_tokens(char **pre_token);

// SIG
void	siging_handler(int sig);

// check_error.c
int		check_syntax_errors(t_token *tokens);

//free_utils
void	free_array_str(char **str);
void	free_cmd(t_cmd *cmd);
void	free_token(t_token *token);
void	free_env(t_env *env);
void	free_export_add_env(t_env *new, char **arg);
void	free_all(t_cmd *cmd, t_token *token, t_env *env, char *line);
void	free_split(char **split_arg);

#endif