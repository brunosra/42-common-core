/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_empty_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:22:20 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/05 18:25:03 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token			*ft_handle_empty_tokens(t_token *tokens);
static int		ft_count_valid_tokens(t_token *tokens, int *count);
static t_token	*ft_rebuild_tokens(t_token *tokens);
static void		ft_copy_valid_tokens(t_token *tokens, t_token *new_tokens);

/**
 * @brief  Processes the token list, removing TKN_EMPTY and reassigning types.
 * 
 * @param  tokens  The original token array.
 * @return t_token*  The processed token array.
 */
t_token	*ft_handle_empty_tokens(t_token *tokens)
{
	t_token	*new_tokens;
	int		has_empty;
	int		count;

	if (!tokens)
		return (NULL);
	has_empty = ft_count_valid_tokens(tokens, &count);
	if (!has_empty)
		return (tokens);
	new_tokens = ft_rebuild_tokens(tokens);
	return (new_tokens);
}

/**
 * @brief  Counts the valid tokens (excluding TKN_EMPTY).
 * 
 * @param  tokens  The original array of tokens.
 * @param  count   Pointer to store the number of valid tokens.
 * @return int     1 if TKN_EMPTY exists, 0 otherwise.
 */
static int	ft_count_valid_tokens(t_token *tokens, int *count)
{
	int	i;
	int	has_empty;

	i = 0;
	*count = 0;
	has_empty = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TKN_EPTY)
			has_empty = 1;
		else
			(*count)++;
		i++;
	}
	return (has_empty);
}

/**
 * @brief  Removes TKN_EMPTY tokens and recalculates token types.
 * 
 * @param  tokens  The original array of tokens.
 * @return t_token*  A new token array without empty tokens.
 */
/**
 * @brief  Rebuilds the token array, removing TKN_EMPTY and reassigning types.
 * 
 * @param  tokens  The original token array.
 * @return t_token*  The rebuilt token array.
 */
t_token	*ft_rebuild_tokens(t_token *tokens)
{
	t_token	*new_tokens;
	int		count;
	int		i;
	t_type	prev_type;

	if (!tokens)
		return (NULL);
	if (ft_count_valid_tokens(tokens, &count) == 0)
		return (tokens);
	new_tokens = ft_calloc(sizeof(t_token), (count + 1));
	if (!new_tokens)
		return (NULL);
	ft_copy_valid_tokens(tokens, new_tokens);
	ft_free_tokens(tokens);
	i = 0;
	prev_type = TKN_NULL;
	while (new_tokens[i].value)
	{
		new_tokens[i].type = ft_get_token_type(new_tokens[i].value, prev_type);
		prev_type = new_tokens[i].type;
		i++;
	}
	new_tokens[i].type = TKN_NULL;
	new_tokens[i].value = NULL;
	return (new_tokens);
}

/**
 * @brief  Copies valid tokens (excluding TKN_EMPTY) into a new array.
 * 
 * @param  tokens     The original array of tokens.
 * @param  new_tokens The new array to store valid tokens.
 */
static void	ft_copy_valid_tokens(t_token *tokens, t_token *new_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type != TKN_EPTY)
		{
			new_tokens[j].value = ft_strdup(tokens[i].value);
			new_tokens[j].type = TKN_NULL;
			j++;
		}
		i++;
	}
	new_tokens[j].value = NULL;
	new_tokens[j].type = TKN_NULL;
}
