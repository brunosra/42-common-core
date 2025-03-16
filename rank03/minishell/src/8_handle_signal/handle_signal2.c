/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 08:24:42 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/10 07:10:02 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_fork_signals(void);
void	ft_sigint_fork_handler(int sig);
void	ft_sigterm_pipe_handler(int sig);
void	ft_set_pipe_signals(void);
void	ft_sigint_pipe_handler(int sig);

/**
 * @brief Configures signal handling for child processes.
 * 
 * In a forked process, SIGINT and SIGQUIT are ignored to prevent interruption
 * unless explicitly handled in execution.
 */
void	ft_set_fork_signals(void)
{
	signal(SIGINT, ft_sigint_fork_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, ft_sigterm_pipe_handler);
}

/**
 * @brief  Handles SIGINT signal in a forked process.
 * 
 * When a child process receives SIGINT (Ctrl+C), this function ensures
 * it exits with code 130, following the standard shell behavior.
 * 
 * @param  sig  Received signal (expected SIGINT).
 */
void	ft_sigint_fork_handler(int sig)
{
	if (sig == SIGINT)
		ft_exit_code(130);
}

/**
 * @brief  Handles signals for pipe child processes.
 * 
 * @param  sig  The received signal.
 * 
 * If the process receives SIGTERM, it frees the minishell structure 
 * and exits safely to prevent zombie processes.
 */
void	ft_sigterm_pipe_handler(int sig)
{
	t_minishell	*ms;

	if (sig == SIGTERM)
	{
		ms = ft_ms_struct(NULL, 1);
		ft_free_ms(ms, true, true, -1);
		exit(-1);
	}
}

/**
 * @brief  Configures signal handling for child processes in a pipe.
 * 
 * This function ensures that:
 * - SIGTERM is handled to clean up processes properly.
 * - SIGQUIT (Ctrl + \) is ignored.
 * - SIGINT (Ctrl + C) is ignored to prevent premature termination.
 */
void	ft_set_pipe_signals(void)
{
	signal(SIGTERM, ft_sigterm_pipe_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_pipe_handler);
}

/**
 * @brief  Handles SIGTERM signal in a piped command execution.
 * 
 * If a process inside a pipe receives SIGTERM, this function ensures
 * the shell properly cleans up and exits with code 130 (Ctrl+C behavior).
 * 
 * @param  sig  Received signal (expected SIGTERM).
 */
void	ft_sigint_pipe_handler(int sig)
{
	t_minishell	*ms;

	if (sig == SIGTERM)
	{
		ms = ft_ms_struct(NULL, 1);
		ft_free_ms(ms, true, true, -1);
		ft_exit_code(130);
		exit(130);
	}
}
