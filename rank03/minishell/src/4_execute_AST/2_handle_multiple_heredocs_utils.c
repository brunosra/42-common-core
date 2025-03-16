/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_multiple_heredocs_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:21:48 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/03 02:19:02 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_finalize_heredoc(t_minishell *ms, int *i);
int			ft_collect_heredocs(t_node *node, t_minishell *ms);
static int	ft_allocate_heredoc_stops(t_node *node, t_minishell *ms);
int			ft_multiple_heredoc_syntax_error(t_node *current);

/**
 * @brief  Finalizes heredoc processing and writes to pipe if needed.
 * 
 * @param  ms    Pointer to the minishell structure.
 * @param  node  Pointer to the AST node.
 * @param  i     Pointer to heredoc index.
 */
void	ft_finalize_heredoc(t_minishell *ms, int *i)
{
	char	*new_temp;

	if (ms->temp && ms->c_multi_heredocs == *i + 1)
	{
		new_temp = ft_strjoin_free(ms->temp, "\n", 1, 0);
		ft_revalue_heredoc_input(&new_temp, ms);
		ft_putstr_fd(new_temp, ms->pipefd[1]);
		free(new_temp);
	}
	else
		free(ms->temp);
	close(ms->pipefd[1]);
	exit(ft_free_ms(ms, true, true, 0));
}

/**
 * @brief  Collects all heredocs from the current node and its left branch.
 * 
 * @param  node  Pointer to the starting heredoc node in the AST.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Status of the collection.
 **         0 on success.
 **         Non-zero in case of syntax errors.
 */
int	ft_collect_heredocs(t_node *node, t_minishell *ms)
{
	t_node	*current;

	ms->c_multi_heredocs = 0;
	if (!node || node->token->type != TKN_HDOC)
		return (0);
	current = node;
	while (current && current->token->type == TKN_HDOC)
	{
		ms->c_multi_heredocs++;
		current = current->left;
	}
	return (ft_allocate_heredoc_stops(node, ms));
}

/**
 * @brief  Allocates and populates heredoc stop tokens.
 * 
 * @param  node  Pointer to the starting heredoc node in the AST.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Returns 0 on success, 1 on error.
 */
static int	ft_allocate_heredoc_stops(t_node *node, t_minishell *ms)
{
	t_node	*current;
	int		i;

	node->heredoc_stops = malloc(sizeof(char *) * (ms->c_multi_heredocs + 1));
	if (!node->heredoc_stops)
		return (0);
	current = node;
	i = ms->c_multi_heredocs;
	while (current && --i >= 0)
	{
		if (!current->right)
			return (ft_multiple_heredoc_syntax_error(current));
		node->heredoc_stops[i] = current->right->token->value;
		current = current->left;
	}
	node->heredoc_stops[ms->c_multi_heredocs] = NULL;
	return (0);
}

/**
 * @brief  Handles syntax errors in heredoc collection.
 * 
 * @param  current  Pointer to the current node in the AST.
 * @param  ms       Pointer to the minishell structure.
 * @return int      Returns 1 to indicate an error.
 */
int	ft_multiple_heredoc_syntax_error(t_node *current)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd(current->left->token->value[0], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ft_exit_code(2);
	return (1);
}
