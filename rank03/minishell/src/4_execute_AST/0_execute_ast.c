/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_execute_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:05:11 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/08 04:28:35 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_execute_ast(t_node *node, t_minishell *ms);
static int	ft_handle_syntax_error(t_node *node);
static int	ft_execute_output_redirect(t_node *node, t_minishell *ms);
static int	ft_execute_input_redirect(t_node *node, t_minishell *ms);
static int	ft_execute_heredoc(t_node *node, t_minishell *ms);

/**
 * @brief  Executes the AST based on the current node type.
 * 
 * @param  node  Pointer to the current AST node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 *         0 on success.
 *         Non-zero in case of errors or syntax issues.
 */
int	ft_execute_ast(t_node *node, t_minishell *ms)
{
	if (!node || !ms->n_args)
		return (1);
	if (node->token->type == TKN_EXCPT)
		return (ft_handle_syntax_error(node));
	if (node->token->type == TKN_OUT_RD)
		return (ft_execute_output_redirect(node, ms));
	if (node->token->type == TKN_IN_RD)
		return (ft_execute_input_redirect(node, ms));
	if (node->token->type == TKN_HDOC)
		return (ft_execute_heredoc(node, ms));
	if (node->token->type == TKN_PIPE)
		return (ft_handle_pipe(node, ms));
	if (node->token->type == TKN_BLTIN
		|| node->token->type == TKN_CMD)
		return (ft_execute_command(node, ms));
	return (0);
}

/**
 * @brief  Handles syntax errors related to unexpected tokens.
 * 
 * @param  node  Pointer to the AST node with the error.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Always returns 1 to indicate an error.
 */
static int	ft_handle_syntax_error(t_node *node)
{
	ft_putstr_three_fd("minishell: syntax error near unexpected token `",
		node->token->value, "'\n", STDERR_FILENO);
	ft_exit_code(2);
	return (1);
}

/**
 * @brief  Handles output redirection in the AST execution.
 * 
 * @param  node  Pointer to the output redirection node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 */
static int	ft_execute_output_redirect(t_node *node, t_minishell *ms)
{
	if (ms->swap_output_redirects == false)
	{
		ft_swap_redirects_values(node, TKN_OUT_RD);
		ms->swap_output_redirects = true;
	}
	return (ft_handle_output_redirect(node, ms));
}

/**
 * @brief  Handles input redirection in the AST execution.
 * 
 * @param  node  Pointer to the input redirection node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 */
static int	ft_execute_input_redirect(t_node *node, t_minishell *ms)
{
	if (ms->swap_input_redirects == false)
	{
		ft_swap_redirects_values(node, TKN_IN_RD);
		ms->swap_input_redirects = true;
	}
	return (ft_handle_input_redirect(node, ms, -1));
}

/**
 * @brief  Handles heredoc execution in the AST.
 * 
 * @param  node  Pointer to the heredoc node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 */
static int	ft_execute_heredoc(t_node *node, t_minishell *ms)
{
	if (node->left && node->left->token->type == TKN_HDOC)
	{
		if (ft_collect_heredocs(node, ms))
			return (1);
		return (ft_handle_multiple_heredocs(node, ms));
	}
	return (ft_handle_heredoc(node, ms));
}
