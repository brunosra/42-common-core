/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_group_command_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:47:36 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/03 16:48:08 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node		*ft_group_command_tokens(t_token *tokens, int *index);
static void	ft_process_cmd_value(t_node *cmd_node, t_cmd_helper *h);
static void	ft_fill_cmd_node(t_token *tokens, int *index, t_node *cmd_node,
				t_cmd_helper *h);
static void	ft_handle_individual_token(t_token *tokens, int *index,
				t_node *cmd_node, t_cmd_helper *h);
static void	ft_handle_redirects(t_token *tokens, int *index, t_cmd_helper *h);

/**
 * @brief  Groups command-related tokens into a single command node.
 * 
 * This function groups tokens related to a single command, processing
 * arguments, redirects, and command values, and returns a command node
 * that represents the complete command structure with associated values.
 * 
 * @param tokens  An array of tokens.
 * @param index   A pointer to the current index in the tokens array.
 * 
 * @return t_node*  A pointer to the command node.
 */
t_node	*ft_group_command_tokens(t_token *tokens, int *index)
{
	t_node			*cmd_node;
	t_cmd_helper	h;

	cmd_node = ft_create_cmd_node(&tokens[*index]);
	h = ft_init_cmd_helper(cmd_node);
	(*index)++;
	ft_collect_arguments(tokens, index, &h);
	h.stop = *index;
	ft_handle_redirects(tokens, index, &h);
	cmd_node->cmd_ready = malloc(sizeof(char *)
			* (h.arg_count + (h.n_args_cmd_nd_values - 1) + 1));
	if (!cmd_node->cmd_ready)
		return (NULL);
	ft_process_cmd_value(cmd_node, &h);
	*index -= (h.arg_count + h.c_except + h.empty);
	ft_fill_cmd_node(tokens, index, cmd_node, &h);
	if (h.c_except)
		*index = h.stop;
	cmd_node->cmd_ready[h.i] = NULL;
	if (cmd_node->cmd_ready[0])
		cmd_node->cmd_ready = ft_remove_null_values(cmd_node->cmd_ready,
				h.arg_count);
	return (cmd_node);
}

/**
 * @brief  Handles redirects and counts special cases.
 * 
 * This function processes tokens that represent redirects (input,
 * output, heredoc) or filenames and updates the helper structure
 * accordingly, including special handling for redirects.
 * 
 * @param tokens  An array of tokens.
 * @param index   A pointer to the current index in the tokens array.
 * @param h       A pointer to the helper structure.
 */
static void	ft_handle_redirects(t_token *tokens, int *index, t_cmd_helper *h)
{
	while (tokens[*index].value && (tokens[*index].type != TKN_PIPE
			&& tokens[*index].type != TKN_EXCPT
			&& tokens[*index].type != TKN_CMD))
	{
		if (tokens[*index].type == TKN_IN_RD
			|| tokens[*index].type == TKN_OUT_RD
			|| tokens[*index].type == TKN_HDOC
			|| tokens[*index].type == TKN_FILE)
		{
			h->c_except++;
			(*index)++;
			if (tokens[*index].type == TKN_FILE)
			{
				h->c_except++;
				(*index)++;
			}
		}
		ft_collect_arguments(tokens, index, h);
	}
}

/**
 * @brief  Handles an individual token and updates the cmd node's `cmd_ready`.
 * 
 * This helper function processes an individual token, checking if the
 * token value is empty and skipping it if necessary. It also removes
 * quotes from the token's value if required and then copies the value
 * to the command node's `cmd_ready` array.
 * 
 * @param tokens   An array of tokens.
 * @param index    A pointer to the current index in the tokens array.
 * @param cmd_node A pointer to the command node to be filled.
 * @param h        A pointer to the helper structure.
 */
static void	ft_handle_individual_token(t_token *tokens, int *index,
										t_node *cmd_node, t_cmd_helper *h)
{
	if (tokens[*index].value[0] == '\0')
	{
		(*index)++;
		return ;
	}
	if (h->i > h->j && (ft_cmp_str_str(tokens[*index].value, "'",
				ft_strlen(tokens[*index].value))
			|| ft_cmp_str_str(tokens[*index].value,
				"\"", ft_strlen(tokens[*index].value))))
		tokens[*index].value = ft_remove_quotes(tokens[*index].value);
	cmd_node->cmd_ready[h->i] = ft_strdup(tokens[*index].value);
	h->i++;
	(*index)++;
}

/**
 * @brief  Fills the command node with token values.
 * 
 * This function fills the command node's `cmd_ready` array with token
 * values from the tokens array. It processes argument and redirection
 * tokens, removing quotes from arguments if necessary.
 * 
 * @param tokens   An array of tokens.
 * @param index    A pointer to the current index in the tokens array.
 * @param cmd_node A pointer to the command node to be filled.
 * @param h        A pointer to the helper structure.
 */
static void	ft_fill_cmd_node(t_token *tokens, int *index, t_node *cmd_node,
								t_cmd_helper *h)
{
	h->i = h->j;
	if (h->n_args_cmd_nd_values != 1)
		h->arg_count += h->n_args_cmd_nd_values;
	while (h->i < h->arg_count)
	{
		if (tokens[*index].value && (tokens[*index].type == TKN_ARG
				|| tokens[*index].type == TKN_VAR
				|| tokens[*index].type == TKN_CMD
				|| tokens[*index].type == TKN_BLTIN))
		{
			ft_handle_individual_token(tokens, index, cmd_node, h);
		}
		else if ((tokens[*index].type == TKN_IN_RD
				|| tokens[*index].type == TKN_OUT_RD
				|| tokens[*index].type == TKN_HDOC
				|| tokens[*index].type == TKN_FILE))
			(*index)++;
		else
			break ;
	}
}

/**
 * @brief  Processes the command node value, handling spaces and quotes.
 * 
 * This function processes the value of the command node, handling spaces
 * by splitting the value into multiple parts and quotes by removing them
 * from the value.
 * 
 * @param cmd_node A pointer to the command node.
 * @param h        A pointer to the helper structure.
 */
static void	ft_process_cmd_value(t_node *cmd_node, t_cmd_helper *h)
{
	if (h->n_args_cmd_nd_values > 1)
	{
		h->cmd_nd_value = ft_split(cmd_node->token->value, ' ');
		while (h->cmd_nd_value[h->j])
		{
			cmd_node->cmd_ready[h->j] = ft_strdup(h->cmd_nd_value[h->j]);
			h->j++;
		}
		ft_free_split(h->cmd_nd_value);
		h->arg_count--;
	}
	else if (ft_cmp_str_str(cmd_node->token->value, "\"", h->len_value)
		|| ft_cmp_str_str(cmd_node->token->value, "'", h->len_value))
		cmd_node->token->value = ft_remove_quotes(cmd_node->token->value);
}
