/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handle_heredoc_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:12:40 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 18:03:51 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_heredoc(t_minishell *ms, t_node *node, char *temp);
void	ft_restore_stdin(t_minishell *ms);
int		ft_handle_exit_status(t_minishell *ms, t_node *node);
int		ft_redirect_stdout(t_minishell *ms);
void	ft_dup2_error(t_minishell *ms, int tty_fd, int save_stdout);

/**
 * @brief  Writes the heredoc content to the pipe.
 * 
 * @param  ms    Pointer to the minishell structure.
 * @param  node  Pointer to the heredoc node.
 * @param  temp  Buffer containing heredoc content.
 */
void	ft_write_heredoc(t_minishell *ms, t_node *node, char *temp)
{
	if (temp)
	{
		if (node->right && node->right->token->old_value[0] != '"'
			&& node->right->token->old_value[0] != '\'')
			ft_revalue_heredoc_input(&temp, ms);
		write(ms->pipefd[1], temp, ft_strlen(temp));
		free(temp);
	}
}

/**
 * @brief  Restores stdin from the pipe.
 * 
 * @param  ms  Pointer to the minishell structure.
 */
void	ft_restore_stdin(t_minishell *ms)
{
	if (dup2(ms->pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(ms->pipefd[0]);
		ft_exit_code(1);
	}
	close(ms->pipefd[0]);
}

/**
 * @brief  Handles the exit status after the heredoc process.
 * 
 * @param  ms    Pointer to the minishell structure.
 * @param  node  Pointer to the heredoc node.
 * @return int   Execution status.
 */
int	ft_handle_exit_status(t_minishell *ms, t_node *node)
{
	if (WIFEXITED(ms->status))
		ft_exit_code(WEXITSTATUS(ms->status));
	if (WIFEXITED(ms->status) && WEXITSTATUS(ms->status) == 130)
	{
		ft_exit_code(130);
		return (1);
	}
	else
		ft_exit_code(1);
	return (ft_execute_ast(node->left, ms));
}

/**
 * @brief  Redirects STDOUT to /dev/tty when needed.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  File descriptor of saved stdout.
 */
int	ft_redirect_stdout(t_minishell *ms)
{
	int	save_stdout;
	int	tty_fd;

	save_stdout = ft_duplicate_stdout(ms);
	if (save_stdout == -1)
		return (-1);
	tty_fd = ft_open_tty(ms, save_stdout);
	if (tty_fd == -1)
		return (-1);
	if (dup2(ms->save_stdout, STDOUT_FILENO) == -1)
	{
		ft_dup2_error(ms, tty_fd, save_stdout);
		return (-1);
	}
	close(tty_fd);
	return (save_stdout);
}

/**
 * @brief  Handles dup2 errors and cleans up resources.
 * 
 * @param  ms           Pointer to the minishell structure.
 * @param  tty_fd       File descriptor of /dev/tty.
 * @param  save_stdout  Saved stdout file descriptor.
 */
void	ft_dup2_error(t_minishell *ms, int tty_fd, int save_stdout)
{
	perror("dup2");
	close(tty_fd);
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
	close(ms->save_stdout);
	close(save_stdout);
	ft_exit_code(1);
}
