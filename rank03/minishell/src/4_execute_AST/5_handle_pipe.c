/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_handle_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:35:12 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/13 01:13:06 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				ft_handle_pipe(t_node *node, t_minishell *ms);
static void		ft_execute_pipe_child(t_node *node, t_minishell *ms);
static void		ft_handle_pipe_exit(pid_t pid1, pid_t pid2, int pid_terminated,
					int status1);
static int		ft_fork_pipe_child(t_node *node, t_minishell *ms, pid_t *pid1);
static pid_t	ft_fork_pipe_right_child(t_node *node, t_minishell *ms);

/**
 * @brief  Handles execution of a pipe between two commands.
 * 
 * This function sets up the pipe, forks two child processes to execute
 * the left and right commands, and ensures proper process management.
 * 
 * @param  node  Pointer to the pipe node in the AST.
 * @param  ms    Pointer to the minishell structure.
 * @return int   
 *         - 2 if there is a syntax error.
 *         - 1 if a fork or pipe creation fails.
 *         - 0 if successful.
 */
int	ft_handle_pipe(t_node *node, t_minishell *ms)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		pid_terminated;

	status1 = -1;
	if (ft_check_pipe_syntax(node, ms))
	{
		ft_exit_code(2);
		return (2);
	}
	if (ft_create_pipe(ms))
		return (1);
	if (ft_fork_pipe_child(node, ms, &pid1) == -1)
		return (1);
	if (ft_redirect_pipe_input(ms))
		return (1);
	pid2 = ft_fork_pipe_right_child(node, ms);
	if (pid2 == -1)
		return (1);
	pid_terminated = waitpid(-1, &status1, 0);
	ft_handle_pipe_exit(pid1, pid2, pid_terminated, status1);
	return (ft_exit_code(-1));
}

/**
 * @brief  Forks and executes the left-side command in a pipe.
 * 
 * @param  node  Pointer to the AST node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   0 on success, -1 on fork error.
 */
static int	ft_fork_pipe_child(t_node *node, t_minishell *ms, pid_t *pid1)
{
	*pid1 = fork();
	if (*pid1 == -1)
		return (ft_handle_fork_error());
	ft_set_fork_signals();
	if (*pid1 == 0)
		ft_execute_pipe_child(node, ms);
	close(ms->pipefd[1]);
	return (0);
}

/**
 * @brief  Forks and executes the right-side command in a pipe.
 * 
 * @param  node  Pointer to the AST node.
 * @param  ms    Pointer to the minishell structure.
 * @return pid_t PID of the created child process, or -1 on error.
 */
static pid_t	ft_fork_pipe_right_child(t_node *node, t_minishell *ms)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		ft_execute_ast(node->right, ms);
		ft_free_ms(ms, true, true, 0);
		exit(ft_exit_code(-1));
	}
	return (pid2);
}

/**
 * @brief  Handles process termination for a pipeline.
 * 
 * @param  ms              Pointer to the minishell structure.
 * @param  pid_terminated  PID of the process that terminated first.
 * @param  pid2            PID of the second child process.
 * @param  status1         Status of the first terminated process.
 */
static void	ft_handle_pipe_exit(pid_t pid1, pid_t pid2, int pid_terminated,
								int status1)
{
	int	status2;

	status2 = -1;
	if (pid_terminated == pid2)
	{
		status2 = WEXITSTATUS(status1);
		ft_sleep();
		kill(pid1, SIGTERM);
		waitpid(pid1, NULL, 0);
		ft_exit_code(status2);
	}
	else if (pid_terminated == pid1)
	{
		waitpid(pid2, &status2, 0);
		ft_exit_code(WEXITSTATUS(status2));
	}
}

/**
 * @brief  Executes the left side of the pipe in the child process.
 * 
 * @param  node  Pointer to the pipe node.
 * @param  ms    Pointer to the minishell structure.
 */
static void	ft_execute_pipe_child(t_node *node, t_minishell *ms)
{
	ft_set_heredoc_signals();
	close(ms->pipefd[0]);
	if (dup2(ms->pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(ms->pipefd[1]);
	ft_execute_ast(node->left, ms);
	exit(ft_free_ms(ms, true, true, ft_exit_code(-1)));
}
