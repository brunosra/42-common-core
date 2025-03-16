/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:08:34 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/06 04:29:30 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_handle_heredoc(t_node *node, t_minishell *ms);
int			ft_heredoc_syntax_error(void);
int			ft_handle_heredoc_fork_error(t_minishell *ms);
static void	ft_heredoc_child_process(t_node *node, t_minishell *ms);
static char	*ft_update_heredoc_buffer(char *temp, char *input);

/**
 * @brief  Handles heredoc redirection by reading user input until a delimiter
 * is reached.
 * 
 * @param  node  Pointer to the heredoc node in the AST.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 **         0 on success.
 **         Non-zero in case of errors or syntax issues.
 */
int	ft_handle_heredoc(t_node *node, t_minishell *ms)
{
	int	save_stdout;
	int	pipe_status;

	save_stdout = -1;
	if (!node->right)
		return (ft_heredoc_syntax_error());
	pipe_status = ft_create_pipe(ms);
	if (pipe_status)
		return (pipe_status);
	if (!isatty(STDOUT_FILENO))
		save_stdout = ft_redirect_stdout(ms);
	ms->pid = fork();
	if (ms->pid == -1)
		return (ft_handle_heredoc_fork_error(ms));
	ft_set_fork_signals();
	if (ms->pid == 0)
		ft_heredoc_child_process(node, ms);
	close(ms->pipefd[1]);
	waitpid(ms->pid, &ms->status, 0);
	ft_set_main_signals();
	ft_restore_stdin(ms);
	if (save_stdout != -1)
		ft_restore_stdout(save_stdout);
	return (ft_handle_exit_status(ms, node));
}

/**
 * @brief  Handles syntax errors in heredoc usage.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  Always returns 1 (error).
 */
int	ft_heredoc_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		STDERR_FILENO);
	ft_exit_code(2);
	return (1);
}

/**
 * @brief  Handles a fork error.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  Always returns 1 (error).
 */
int	ft_handle_heredoc_fork_error(t_minishell *ms)
{
	perror("fork");
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
	ft_exit_code(1);
	return (1);
}

/**
 * @brief  Handles the child process for heredoc input.
 * 
 * @param  node  Pointer to the heredoc node.
 * @param  ms    Pointer to the minishell structure.
 */
static void	ft_heredoc_child_process(t_node *node, t_minishell *ms)
{
	char	*input;

	ft_set_heredoc_signals();
	close(ms->pipefd[0]);
	ms->temp = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_three_fd("minishell: warning: here-document delimited by"
				" EOF (wanted `", node->right->token->value, "')\n",
				STDERR_FILENO);
			break ;
		}
		if (!ft_strcmp(input, node->right->token->value))
			break ;
		ms->temp = ft_update_heredoc_buffer(ms->temp, input);
		free(input);
	}
	ft_write_heredoc(ms, node, ms->temp);
	close(ms->pipefd[1]);
	exit(ft_free_ms(ms, true, true, 0));
}

/**
 * @brief  Appends user input to the heredoc buffer.
 * 
 * @param  temp  Current buffer.
 * @param  input User input line.
 * @return char* Updated buffer.
 */
static char	*ft_update_heredoc_buffer(char *temp, char *input)
{
	char	*new_temp;

	if (temp)
	{
		new_temp = ft_strjoin_free(temp, input, 1, 0);
		new_temp = ft_strjoin_free(new_temp, "\n", 1, 0);
	}
	else
	{
		new_temp = ft_strdup(input);
		new_temp = ft_strjoin_free(new_temp, "\n", 1, 0);
	}
	return (new_temp);
}
