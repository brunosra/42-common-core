/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_group_command_tokens_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:51:34 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 00:46:41 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			ft_collect_arguments(t_token *tokens, int *index,
					t_cmd_helper *h);
t_cmd_helper	ft_init_cmd_helper(t_node *cmd_node);
int				ft_verify_cmd_node_value(t_node *cmd_node);

/**
 * @brief  Initializes a helper structure to group command tokens.
 * 
 * This function initializes a structure that is used to keep track of
 * various states during the process of handling command tokens, including
 * the argument count, token value length, and the number of arguments.
 * 
 * @param cmd_node  A pointer to the node representing the command.
 * 
 * @return t_cmd_helper  The initialized helper structure.
 */
t_cmd_helper	ft_init_cmd_helper(t_node *cmd_node)
{
	t_cmd_helper	h;

	h.cmd_nd_value = NULL;
	h.arg_count = 1;
	h.i = 0;
	h.j = 0;
	h.len_value = ft_strlen(cmd_node->token->value);
	h.n_args_cmd_nd_values = ft_verify_cmd_node_value(cmd_node);
	h.c_except = 0;
	h.empty = 0;
	return (h);
}

/**
 * @brief  Counts arguments and handles empty values.
 * 
 * This function processes the tokens from the provided index and counts
 * the number of arguments, incrementing the argument count for valid
 * tokens while handling empty values by incrementing a separate counter.
 * 
 * @param tokens  An array of tokens.
 * @param index   A pointer to the current index in the tokens array.
 * @param h       A pointer to the helper structure.
 */
void	ft_collect_arguments(t_token *tokens, int *index, t_cmd_helper *h)
{
	while (tokens[*index].value
		&& (tokens[*index].type == TKN_ARG
			|| tokens[*index].type == TKN_VAR))
	{
		if (tokens[*index].value[0] == '\0')
		{
			(*index)++;
			h->empty++;
		}
		else
		{
			h->arg_count++;
			(*index)++;
		}
	}
}

/**
 * @brief  Verifies the number of arguments within a command node value.
 * 
 * @param  cmd_node  Command node to evaluate.
 * @return int       Number of arguments found within the command node value.
 */
int	ft_verify_cmd_node_value(t_node *cmd_node)
{
	int		i;
	int		count;
	char	*value;

	i = 0;
	count = 0;
	value = cmd_node->token->value;
	if (value[i] == '"' || value[i] == '\'')
		return (1);
	while (value[i])
	{
		if (value[i] && value[i] != ' ')
			count++;
		while (value[i] && value[i] != ' ')
			i++;
		while (value[i] && value[i] == ' ')
			i++;
	}
	return (count);
}
