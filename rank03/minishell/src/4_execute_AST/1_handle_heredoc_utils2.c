/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:18:16 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 18:32:06 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_duplicate_stdout(t_minishell *ms);
int		ft_open_tty(t_minishell *ms, int save_stdout);
void	ft_restore_stdout(int save_stdout);

/**
 * @brief  Duplicates STDOUT file descriptor.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  Duplicated file descriptor or -1 on error.
 */
int	ft_duplicate_stdout(t_minishell *ms)
{
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	if (save_stdout == -1)
	{
		perror("dup");
		close(ms->pipefd[0]);
		close(ms->pipefd[1]);
		ft_exit_code(1);
	}
	return (save_stdout);
}

/**
 * @brief  Opens /dev/tty for writing.
 * 
 * @param  ms           Pointer to the minishell structure.
 * @param  save_stdout  Saved stdout file descriptor.
 * @return int          File descriptor of /dev/tty or -1 on error.
 */
int	ft_open_tty(t_minishell *ms, int save_stdout)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd == -1)
	{
		perror("open /dev/tty");
		close(ms->pipefd[0]);
		close(ms->pipefd[1]);
		close(save_stdout);
		ft_exit_code(1);
	}
	return (tty_fd);
}

/**
 * @brief  Restores the original STDOUT.
 * 
 * @param  save_stdout  File descriptor of the saved stdout.
 */
void	ft_restore_stdout(int save_stdout)
{
	if (dup2(save_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(save_stdout);
		ft_exit_code(1);
	}
	close(save_stdout);
}
