/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:12:04 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/13 18:55:32 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errors.h"
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_ast_node	t_node;

/**__Lexing__**/
typedef enum e_token_type
{
	TKN_CMD,
	TKN_ARG,
	TKN_PIPE,
	TKN_FILE,
	TKN_VAR,
	TKN_OUT_RD,
	TKN_IN_RD,
	TKN_HDOC,
	TKN_BLTIN,
	TKN_NULL,
	TKN_EXCPT,
	TKN_EPTY,
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
	char	*old_value;

}	t_token;

/**__Parsing__**/
typedef struct s_ast_node
{
	t_token	*token;
	char	**cmd_ready;
	t_node	*left;
	t_node	*right;
	t_node	*prev;
	bool	file;
	bool	file_unlink;
	char	**heredoc_stops;
}	t_node;

/**__Handle_ENV__**/
typedef struct s_env
{
	char	**envp;
	char	*env_paths;
	char	**paths;
	char	*full_path;
	char	**export;
}	t_env;

typedef struct s_minishell
{
	char	*input;
	t_token	*tokens;
	t_node	*ast_root;
	t_env	env;
	int		status;
	int		save_stdin;
	int		save_stdout;
	int		n_args;
	pid_t	pid;
	int		pipefd[2];
	bool	swap_input_redirects;
	bool	swap_output_redirects;
	int		c_multi_heredocs;
	bool	in_pipe;
	char	*temp;
	int		c_stuck_cats;
	char	*prompt;
	char	currpath[PATH_MAX];
	char	**error_files;
}				t_minishell;

/**
 * @brief Structure to hold AST-related pointers for processing.
 */
typedef struct s_ast_helper
{
	t_node	**current;
	t_node	**root;
	t_node	*op_node;
}	t_ast_helper;

/**
 * @brief Structure to hold grouop_cmd-related variables for processing.
 */
typedef struct s_cmd_helper
{
	int		arg_count;
	int		i;
	int		j;
	int		len_value;
	int		n_args_cmd_nd_values;
	int		c_except;
	int		empty;
	int		stop;
	char	**cmd_nd_value;
}	t_cmd_helper;

/* 0_minishell */
/* minishell.c */
int				main(int argc, char **argv, char **envp);
void			ft_create_prompt(t_minishell *ms);
/* 1_process_input_and_execute.c */
int				ft_process_input_and_execute(t_minishell *ms);
/* 2_handle_exception_pipe_cat.c */
void			ft_trim_last_cat_sequence(t_minishell *ms);
/* 2_handle_exception_pipe_cat2.c */
t_token			*ft_simplify_cat_pipes(t_minishell *ms, t_token *tokens);
/* 3_handle_empty_tokens.c */
t_token			*ft_handle_empty_tokens(t_token *tokens);
/* 4_void		finalize_execution.c */
void			ft_finalize_execution(t_minishell *ms);

/* 1_handle_input */
/* handle_input.c */
int				ft_check_quotes(char *str);
int				ft_count_args(char *str, int i);
int				ft_handle_quotes(char *str, int i, int *start, int *end);

/* 2_lexing_input */
/* 0_tokenize_input.c */
t_token			*ft_tokenize_input(char *str, int n_args, int i, int j);
/* 1_get_token_type.c */
t_type			ft_get_token_type(char *str, t_type prev_type);
/* 2_get_token_type_utils.c */
int				ft_check_builtins(char *str);
int				ft_verify_variable_value(char *str, int i);
/*  3_revalue_quoted_value.c */
char			*ft_revalue_quoted_value(char *value);

/* 3_parsing_AST */
/* 0_parse_ast.c */
t_node			*ft_parse_ast(t_token *tokens);
/* 1_create_nodes.c  */
t_node			*ft_create_cmd_node(t_token *token);
t_node			*ft_create_operator_node(t_token *token, t_node *left,
					t_node *right);
/* 2_group_command_tokens.c */
t_node			*ft_group_command_tokens(t_token *tokens, int *index);
/* 3_group_command_tokens_utils.c */
void			ft_collect_arguments(t_token *tokens, int *index,
					t_cmd_helper *h);
t_cmd_helper	ft_init_cmd_helper(t_node *cmd_node);
int				ft_verify_cmd_node_value(t_node *cmd_node);
/* 4_remove_quotes.c */
char			*ft_remove_quotes(char *value);
/* 5_remove_null_values.c */
char			**ft_remove_null_values(char **cmd_ready, int arg_count);

/* 4_execute_AST */
/* 0_execute_ast.c  */
int				ft_execute_ast(t_node *node, t_minishell *ms);
/* 1_handle_heredoc.c */
int				ft_handle_heredoc(t_node *node, t_minishell *ms);
int				ft_heredoc_syntax_error(void);
int				ft_handle_heredoc_fork_error(t_minishell *ms);
/* 1_handle_heredoc_utils1.c  */
void			ft_write_heredoc(t_minishell *ms, t_node *node, char *temp);
void			ft_restore_stdin(t_minishell *ms);
int				ft_handle_exit_status(t_minishell *ms, t_node *node);
int				ft_redirect_stdout(t_minishell *ms);
void			ft_dup2_error(t_minishell *ms, int tty_fd, int save_stdout);
/* 1_handle_heredoc_utils2.c */
int				ft_duplicate_stdout(t_minishell *ms);
int				ft_open_tty(t_minishell *ms, int save_stdout);
void			ft_restore_stdout(int save_stdout);
/* 2_handle_multiple_heredocs.c  */
int				ft_handle_multiple_heredocs(t_node *node, t_minishell *ms);
/* 2_handle_multiple_heredocs_utils.c */
void			ft_finalize_heredoc(t_minishell *ms, int *i);
int				ft_collect_heredocs(t_node *node, t_minishell *ms);
int				ft_multiple_heredoc_syntax_error(t_node *current);
/* 3_handle_output_redirect.c */
int				ft_handle_output_redirect(t_node *node, t_minishell *ms);
int				ft_check_redirect_syntax(t_node *node);
int				ft_handle_file_error(void);
int				ft_handle_dup_error(int fd);
/* 4_handle_input_redirect.c  */
int				ft_handle_input_redirect(t_node *node, t_minishell *ms, int fd);
int				ft_invalid_right_token_value(char *value);
void			ft_swap_redirects_values(t_node *node, t_type type);
/* 5_handle_pipe.c */
int				ft_handle_pipe(t_node *node, t_minishell *ms);
/* 5_handle_pipe2.c */
int				ft_check_pipe_syntax(t_node *node, t_minishell *ms);
int				ft_redirect_pipe_input(t_minishell *ms);
/* 5_handle_pipe_utils.c  */
int				ft_create_pipe(t_minishell *ms);
int				ft_pipe_syntax_error(char *token, int code);
void			ft_handle_unfinished_pipe(t_minishell *ms, char *input);
int				ft_handle_fork_error(void);
/* 6_execute_command.c */
int				ft_execute_command(t_node *node, t_minishell *ms);
/* 6_execute_command_utils.c */
int				ft_find_executable(t_minishell *ms, char *cmd);
/* 7_validate_file.c */
int				ft_is_valid_file(char *filepath, int mode);
void			ft_remove_created_files(t_node *node);
void			ft_create_files(t_node *node);

/* 5_builtins */
/* builtins.c  */
char			*ft_strtok(char *str, const char *delim);
int				ft_exec_builtins_check(t_node *node, t_minishell *ms);
int				ft_exec_builtins(t_node *node, t_minishell *ms);
/* 1_cd.c */
void			ft_builtin_cd(char **args, t_minishell *ms);
void			ft_rsolve_rel_p(const char *base_p, const char *rel_p,
					char *res_p);
/* 1_cd_utils.c  */
int				ft_builtin_cd_check(char **args, t_minishell *ms);
/* 2_echo.c  */
void			ft_builtin_echo(char **args);
/* 3_env.c */
void			ft_builtin_env(char **args, t_minishell *ms);
/* 4_exit.c */
int				ft_builtin_exit(char **args);
/* 5_export.c */
int				ft_builtin_export_check(char **args);
void			ft_builtin_export(char **args, t_minishell *ms);
int				ft_valid_export_arg(const char *arg);
/* 5_export2.c */
int				ft_process_export(char *str, t_minishell *ms);
/* 5_export_utils.c  */
int				ft_dup_envp(char **envp, char ***dupenv, int count);
void			ft_output_export_1_arg(char **arr, int count);
int				ft_sort_envp(char **dupenv, int count);
void			ft_swap(char **a, char **b);
void			ft_free_str_arr(char **arr);
/* 6_pwd.c */
int				ft_builtin_pwd(void);
/* 7_unset.c */
void			ft_builtin_unset(char **args, t_minishell *ms);

/* 6_handle_env */
/* 0_revalue_tkn_var.c */
int				ft_revalue_tkn_var(t_minishell *ms);
/* 1_check_if_expand.c */
int				ft_check_if_expand(char *str, char *ptr, int heredoc);
int				ft_verify_quotes(char *quote_type, char c);
/* 2_replace_var_value.c */
int				ft_replace_str(char **value, char *key, char *ptr,
					char *env_value);
int				ft_cleanup(char *to_free1, char *to_free2, int error);
int				ft_check_balanced_quotes(char *str, int idx);
/* 3_remove_extra_spaces.c */
int				ft_remove_extra_spaces(char **str);
/* 4_revalue_heredoc_input.c */
int				ft_revalue_heredoc_input(char **input, t_minishell *ms);
/* 5_handle_env_utils.c */
char			**ft_duplicate_envp(char **envp);
char			*ft_get_env_value(const char *str, t_minishell *ms, char **key,
					bool heredoc);
char			*ft_get_env(const char *key, t_minishell *ms);
int				ft_unset_env(const char *key, char **list);
/* 5_handle_env_utils2.c */
int				ft_set_env(const char *key, const char *value, t_minishell *ms);

/* 7_handle_malloc */
/* handle_malloc.c */
void			ft_free_tokens(t_token *tokens);
void			ft_free_ast(t_node *root);
void			ft_free_split(char **str);
int				ft_free_ms(t_minishell *ms, bool free_prompt, bool free_envp,
					int exit);

/* 8_handle_signal */
/* handle_signal.c */
void			ft_signal_handler(int sig);
void			ft_set_main_signals(void);
void			ft_set_heredoc_signals(void);
void			ft_signal_heredoc_handler(int sig);

/* handle_signal2.c */
void			ft_set_fork_signals(void);
void			ft_sigint_fork_handler(int sig);
void			ft_set_pipe_signals(void);
void			ft_sigterm_pipe_handler(int sig);
void			ft_sigint_pipe_handler(int sig);

/* 9_mini_utils */
/* mini_utils_1.c  */
int				ft_perror(char *error, int return_value);
int				ft_putstr_and_return(char *msg, int return_value);
int				ft_exit_code(int newcode);
int				ft_putstr_three_fd(const char *s1, const char *s2,
					const char *s3, int fd);
int				ft_last_left_is_cmd(t_node *node);

/* mini_utils_2.c */
char			*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
t_minishell		*ft_ms_struct(t_minishell *ms, int flag);
void			ft_print_ast(t_node *node, int depth);

/* mini_utils_3.c */
int				ft_has_error_file(t_minishell *ms, char *file);
void			ft_add_error_file(t_minishell *ms, char *file);
void			ft_sleep(void);
#endif