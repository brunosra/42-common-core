/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_handle_input_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:32:06 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/11 02:39:26 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_handle_input_redirect(t_node *node, t_minishell *ms, int fd);
static int	ft_validate_input_file(t_node *node, t_node *root);
int			ft_invalid_right_token_value(char *value);
static int	ft_is_input_also_output(t_node *node, t_node *root);
void		ft_swap_redirects_values(t_node *node, t_type type);

/**
 * @brief Checks if the given input file is also used as an output file.
 * 
 * This function scans the AST to detect cases where a file is both read
 * from (`<`) and written to (`>` or `>>`), which may cause conflicts.
 * 
 * @param node  Pointer to the current input redirection node (`TKN_IN_RD`).
 * @param root  Pointer to the root of the AST.
 * @return int  1 if the file is also an output, 0 otherwise.
 */
static int	ft_is_input_also_output(t_node *node, t_node *root)
{
	t_node	*current;
	char	*filename;

	if (!node || !root || !node->right || node->token->type != TKN_IN_RD)
		return (0);
	filename = node->right->token->value;
	current = root;
	while (current)
	{
		if (current->token->type == TKN_OUT_RD && current->file == true
			&& ft_strcmp(current->right->token->value, filename) == 0)
			return (1);
		if (ft_is_input_also_output(node, current->right))
			return (1);
		if (ft_is_input_also_output(node, current->left))
			return (1);
		current = current->right;
	}
	return (0);
}

/**
 * @brief  Handles input redirection from a file.
 * 
 * @param  node  Pointer to the input redirection node in the AST.
 * @param  ms    Pointer to the minishell structure.
 * @return int   Execution status.
 *         0 on success.
 *         Non-zero in case of errors or syntax issues.
 */
int	ft_handle_input_redirect(t_node *node, t_minishell *ms, int fd)
{
	if (ft_check_redirect_syntax(node))
		return (ft_exit_code(1));
	if (ft_validate_input_file(node, ms->ast_root))
		return (ft_exit_code(1));
	if (ft_is_input_also_output(node, ms->ast_root))
	{
		ft_remove_created_files(ms->ast_root);
		return (ft_exit_code(1));
	}
	fd = open(node->right->token->value, O_RDONLY);
	if (fd == -1 || node->file == true)
	{
		if (!ft_has_error_file(ms, node->right->token->value))
		{
			ft_putstr_three_fd("minishell: ", node->right->token->value,
				": No such file or directory\n", STDERR_FILENO);
			ft_add_error_file(ms, node->right->token->value);
		}
		return (ft_exit_code(1));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_handle_dup_error(fd));
	close(fd);
	ft_exit_code(0);
	return (ft_execute_ast(node->left, ms));
}

/**
 * @brief  Validates the input file before opening it.
 * 
 * @param  node  Pointer to the input redirection node.
 * @param  ms    Pointer to the minishell structure.
 * @return int   1 if the file is invalid, 0 otherwise.
 */
static int	ft_validate_input_file(t_node *node, t_node *root)
{
	if (ft_is_valid_file(node->right->token->value, O_RDONLY))
	{
		ft_remove_created_files(root);
		ft_create_files(node->left);
		ft_exit_code(1);
		return (1);
	}
	return (0);
}

/**
 * @brief  Checks if the token value on the right side is invalid for
 * redirection or other syntax.
 * 
 * @param  value  Token value to check.
 * @return int    Boolean indicating validity.
 **         1 if invalid.
 **         0 if valid.
 */
int	ft_invalid_right_token_value(char *value)
{
	if (!value || ft_strcmp(value, ">") == 0 || ft_strcmp(value, ">>") == 0
		|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, "<<") == 0
		|| ft_strcmp(value, "|") == 0 || ft_strcmp(value, "&&") == 0
		|| ft_strcmp(value, "||") == 0)
		return (1);
	return (0);
}

/**
 * @brief  Swaps the values of redirect nodes to handle nested or reversed cases.
 * 
 * @param  node  Pointer to the current node in the AST.
 * @param  type  Redirect type (input/output).
 */
void	ft_swap_redirects_values(t_node *node, t_type type)
{
	t_node	*current;
	char	*temp_value;

	if (!node || node->token->type != type)
		return ;
	current = node;
	while (current && current->left && current->left->token->type == type)
		current = current->left;
	if (current != node)
	{
		temp_value = current->right->token->value;
		current->right->token->value = node->right->token->value;
		node->right->token->value = temp_value;
	}
}
