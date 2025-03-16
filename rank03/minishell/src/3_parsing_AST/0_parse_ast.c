/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parse_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:34:24 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/07 22:35:26 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node			*ft_parse_ast(t_token *tokens);
static void		ft_process_token(t_token *tokens, int *i, t_node **current,
					t_node **root);
static t_node	*ft_handle_op_node(t_token *tokens, int *i,
					t_node **current, t_node **root);
static void		ft_adjust_input_redirect(t_token *tokens, int *i,
					t_ast_helper *ast);
static t_node	*ft_handle_cmd_node(t_token *tokens, int *i, t_node **current,
					t_node **root);

/**
 * @brief Parses tokens into an Abstract Syntax Tree (AST).
 * 
 * @param tokens      Array of tokens to parse.
 * @return t_node*    Pointer to the root node of the AST.
 */
t_node	*ft_parse_ast(t_token *tokens)
{
	int		i;
	t_node	*root;
	t_node	*current;

	i = 0;
	root = NULL;
	current = NULL;
	while (tokens[i].type != TKN_NULL)
	{
		if (!tokens[i].value && tokens[i].type == TKN_CMD)
			tokens[i].value = ft_strdup("");
		if (tokens[i].type == TKN_ARG)
		{
			i++;
			continue ;
		}
		ft_process_token(tokens, &i, &current, &root);
	}
	if (root)
		root->prev = NULL;
	return (root);
}

/**
 * @brief Handles different types of tokens while parsing AST.
 * 
 * @param tokens      Array of tokens.
 * @param i           Pointer to the current index in tokens.
 * @param current     Pointer to the current node in the AST.
 * @param root        Pointer to the root node of the AST.
 */
static void	ft_process_token(t_token *tokens, int *i, t_node **current,
				t_node **root)
{
	if (tokens[*i].type == TKN_BLTIN || tokens[*i].type == TKN_CMD
		|| tokens[*i].type == TKN_FILE
		|| tokens[*i].type == TKN_ARG)
	{
		if (tokens[*i].type == TKN_FILE)
		{
			tokens[*i].old_value = ft_strdup(tokens[*i].value);
			tokens[*i].value = ft_remove_quotes(tokens[*i].value);
		}
		ft_handle_cmd_node(tokens, i, current, root);
	}
	else if (tokens[*i].type == TKN_PIPE
		|| tokens[*i].type == TKN_OUT_RD
		|| tokens[*i].type == TKN_IN_RD
		|| tokens[*i].type == TKN_HDOC
		|| tokens[*i].type == TKN_EXCPT)
		ft_handle_op_node(tokens, i, current, root);
	else
		(*i)++;
}

/**
 * @brief Handles operator nodes during AST parsing.
 * 
 * @param tokens      Array of tokens to parse.
 * @param i           Pointer to the current index in tokens.
 * @param current     Pointer to the current node in the AST.
 * @param root        Pointer to the root node of the AST.
 * @return t_node*    Created operator node.
 */
static t_node	*ft_handle_op_node(t_token *tokens, int *i,
									t_node **current, t_node **root)
{
	t_ast_helper	ast;

	ast.current = current;
	ast.root = root;
	ast.op_node = ft_create_operator_node(&tokens[*i], *root, NULL);
	ast.op_node->prev = *current;
	if (!*root)
		*root = ast.op_node;
	else if ((*root)->token->type == TKN_PIPE && !(*root)->right
		&& ft_last_left_is_cmd(*root))
	{
		(*root)->right = ast.op_node;
		*current = (*root)->right;
		(*i)++;
		return (ast.op_node);
	}
	else
		(*root)->prev = ast.op_node;
	ft_adjust_input_redirect(tokens, i, &ast);
	return (ast.op_node);
}

/**
 * @brief Adjusts the AST structure when handling input redirection.
 * 
 * @param tokens      Array of tokens.
 * @param i           Pointer to the current index in tokens.
 * @param ast         Helper struct with pointers to AST nodes.
 */
static void	ft_adjust_input_redirect(t_token *tokens, int *i,
				t_ast_helper *ast)
{
	if (tokens[*i].type == TKN_IN_RD && *(ast->current)
		&& (*(ast->current))->prev
		&& (*(ast->current))->prev->right == *(ast->current)
		&& (*(ast->current))->prev->token->type == TKN_PIPE)
	{
		*(ast->root) = (*(ast->current))->prev;
		(*(ast->root))->right = ast->op_node;
		ast->op_node->left = *(ast->current);
		ast->op_node->prev = *(ast->root);
		(*(ast->root))->prev = NULL;
		*(ast->current) = ast->op_node;
		(*i)++;
	}
	else
	{
		*(ast->root) = ast->op_node;
		*(ast->current) = ast->op_node;
		(*i)++;
	}
}

/**
 * @brief Handles command nodes during AST parsing.
 * 
 * @param tokens      Array of tokens to parse.
 * @param i           Pointer to the current index in tokens.
 * @param current     Pointer to the current node in the AST.
 * @param root        Pointer to the root node of the AST.
 * @return t_node*    Created command node.
 */
static t_node	*ft_handle_cmd_node(t_token *tokens, int *i, t_node **current,
									t_node **root)
{
	t_node	*cmd_node;

	if (tokens[*i].type == TKN_BLTIN || tokens[*i].type == TKN_CMD)
		cmd_node = ft_group_command_tokens(tokens, i);
	else
	{
		cmd_node = ft_create_cmd_node(&tokens[*i]);
		(*i)++;
	}
	if (!*root)
		*root = cmd_node;
	else if (*current && ((*current)->token->type == TKN_PIPE
			|| (*current)->token->type == TKN_OUT_RD
			|| (*current)->token->type == TKN_IN_RD
			|| (*current)->token->type == TKN_HDOC
			|| (*current)->token->type == TKN_EXCPT))
		(*current)->right = cmd_node;
	else if (tokens[*i].type != TKN_ARG
		&& cmd_node->token->type != TKN_ARG)
		(*current)->prev->left = cmd_node;
	cmd_node->prev = *current;
	*current = cmd_node;
	return (cmd_node);
}
