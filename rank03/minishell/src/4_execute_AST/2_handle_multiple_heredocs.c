/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_multiple_heredocs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:21:48 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/06 04:40:58 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_handle_multiple_heredocs(t_node *node, t_minishell *ms);
static int	ft_fork_heredoc(t_minishell *ms, t_node *node, int *i);
static void	ft_cleanup_heredocs(t_minishell *ms, int save_stdout, t_node *node);
static void	ft_multiple_heredoc_child(t_node *node, t_minishell *ms, int *i);
static int	ft_process_heredoc_input(t_node *node, t_minishell *ms,
				char *input, int *i);

/**
 * @brief  Handles multiple heredocs consecutively and passes the data.
 * 
 * @param  node  Pointer to the AST node containing multiple heredocs.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 **         0 on success.
 **         Non-zero in case of errors or interruptions.
 */
int	ft_handle_multiple_heredocs(t_node *node, t_minishell *ms)
{
	int		save_stdout;
	int		i;
	int		pipe_status;

	save_stdout = -1;
	ms->temp = NULL;
	i = 0;
	if (!node || !node->heredoc_stops)
		return (1);
	if (!node->right)
		return (ft_heredoc_syntax_error());
	if (!isatty(STDOUT_FILENO))
		save_stdout = ft_redirect_stdout(ms);
	while (node->heredoc_stops[i])
	{
		pipe_status = ft_create_pipe(ms);
		if (pipe_status)
			return (pipe_status);
		if (ft_fork_heredoc(ms, node, &i))
			break ;
		i++;
	}
	ft_cleanup_heredocs(ms, save_stdout, node);
	return (ft_handle_exit_status(ms, node));
}

/**
 * @brief  Creates a fork for processing a single heredoc.
 * 
 * @param  ms    Pointer to the minishell structure.
 * @param  node  Pointer to the current AST node.
 * @param  i     Pointer to heredoc index.
 * @return int   1 if interrupted, 0 otherwise.
 */
static int	ft_fork_heredoc(t_minishell *ms, t_node *node, int *i)
{
	ms->pid = fork();
	if (ms->pid == -1)
		return (ft_handle_heredoc_fork_error(ms));
	ft_set_fork_signals();
	if (ms->pid == 0)
		ft_multiple_heredoc_child(node, ms, i);
	close(ms->pipefd[1]);
	waitpid(ms->pid, &ms->status, 0);
	ft_set_main_signals();
	if (WIFEXITED(ms->status) && WEXITSTATUS(ms->status) == 130)
		return (1);
	return (0);
}

/**
 * @brief  Cleans up heredoc-related processes and restores state.
 * 
 * @param  ms         Pointer to the minishell structure.
 * @param  save_stdout Saved stdout descriptor.
 * @param  node       Pointer to the current AST node.
 */
static void	ft_cleanup_heredocs(t_minishell *ms, int save_stdout, t_node *node)
{
	t_node	*current;
	t_node	*temp_node;

	temp_node = NULL;
	if (WEXITSTATUS(ms->status) != 130)
		ft_restore_stdin(ms);
	close(ms->pipefd[0]);
	if (save_stdout != -1)
		ft_restore_stdout(save_stdout);
	current = node->left;
	while (current && current->token->type == TKN_HDOC)
	{
		temp_node = current;
		current = current->left;
		free(temp_node->right);
		free(temp_node);
	}
	node->left = current;
	if (current)
		current->prev = node;
}

/**
 * @brief  Handles heredoc input for a child process.
 * 
 * @param  node  Pointer to the AST node containing heredoc.
 * @param  ms    Pointer to the minishell structure.
 * @param  i     Pointer to heredoc index.
 */
static void	ft_multiple_heredoc_child(t_node *node, t_minishell *ms, int *i)
{
	char	*input;

	input = NULL;
	ft_set_heredoc_signals();
	close(ms->pipefd[0]);
	while (42)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_three_fd("minishell: warning: here-document delimited by"
				" EOF (wanted `", node->heredoc_stops[*i], "')\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_process_heredoc_input(node, ms, input, i))
			break ;
		free(input);
	}
	ft_finalize_heredoc(ms, i);
}

/**
 * @brief  Processes heredoc input and checks for termination.
 * 
 * @param  node   Pointer to the AST node.
 * @param  ms     Pointer to the minishell structure.
 * @param  input  User input from readline.
 * @param  i      Pointer to heredoc index.
 * @return int    1 if heredoc should stop, 0 otherwise.
 */
static int	ft_process_heredoc_input(t_node *node, t_minishell *ms,
								char *input, int *i)
{
	char	*new_temp;

	if (ft_strcmp(input, node->heredoc_stops[*i]) == 0)
		return (1);
	if (ms->temp == NULL)
		ms->temp = ft_strdup(input);
	else
	{
		new_temp = ft_strjoin_free(ms->temp, "\n", 1, 0);
		ms->temp = ft_strjoin_free(new_temp, input, 1, 0);
	}
	return (0);
}
