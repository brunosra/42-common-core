/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_handle_pipe2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:05:36 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/13 01:11:56 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_check_pipe_syntax(t_node *node, t_minishell *ms);
static void	ft_fork_pipe_process(t_minishell *ms);
static void	ft_handle_pipe_exit_status(t_minishell *ms);
int			ft_redirect_pipe_input(t_minishell *ms);

/**
 * @brief  Checks for syntax errors in pipe usage and handles unfinished pipes.
 * 
 * @param  node  Pointer to the pipe node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   1 if there is a syntax error, 0 otherwise.
 */
int	ft_check_pipe_syntax(t_node *node, t_minishell *ms)
{
	char	*input;
	int		pipe_status;

	if (!node->left)
		return (ft_pipe_syntax_error("|", 2));
	if (node->right)
		return (0);
	pipe_status = ft_create_pipe(ms);
	if (pipe_status)
		return (pipe_status);
	ms->pid = fork();
	if (ms->pid == -1)
		return (ft_handle_heredoc_fork_error(ms));
	ft_set_fork_signals();
	if (ms->pid == 0)
		ft_fork_pipe_process(ms);
	close(ms->pipefd[1]);
	ft_handle_pipe_exit_status(ms);
	input = get_next_line(ms->pipefd[0]);
	close(ms->pipefd[0]);
	if (!input)
		return (0);
	ft_handle_unfinished_pipe(ms, input);
	ft_process_input_and_execute(ms);
	return (1);
}

/**
 * @brief  Handles the forked process for pipe syntax checking.
 * 
 * Reads input from the user until a valid string is provided. If no input
 * is given (CTRL+D), the process exits with an error.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void (Exits process on completion)
 */
static void	ft_fork_pipe_process(t_minishell *ms)
{
	char	*input;

	ft_set_heredoc_signals();
	close(ms->pipefd[0]);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(ft_free_ms(ms, true, true, 2));
		if (*input != '\0')
			break ;
	}
	write(ms->pipefd[1], input, ft_strlen(input));
	free(input);
	close(ms->pipefd[1]);
	exit(ft_free_ms(ms, true, true, 0));
}

/**
 * @brief  Handles the exit status of the forked process.
 * 
 * Waits for the child process to finish and processes exit codes accordingly.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
static void	ft_handle_pipe_exit_status(t_minishell *ms)
{
	waitpid(ms->pid, &ms->status, 0);
	if (WIFEXITED(ms->status) && WEXITSTATUS(ms->status) == 130)
	{
		ft_exit_code(130);
		ms->c_stuck_cats = 0;
		close(ms->pipefd[0]);
	}
	else if (WIFEXITED(ms->status) && WEXITSTATUS(ms->status) == 2)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\nexit\n",
			STDERR_FILENO);
		ft_exit_code(ft_free_ms(ms, true, true, 2));
		exit(ft_exit_code(-1));
	}
}

/**
 * @brief  Redirects pipe output to stdin for the next command.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int 1 if an error occurred, 0 otherwise.
 */
int	ft_redirect_pipe_input(t_minishell *ms)
{
	if (dup2(ms->pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_exit_code(1);
		close(ms->pipefd[0]);
		return (1);
	}
	close(ms->pipefd[0]);
	ft_exit_code(0);
	return (0);
}
