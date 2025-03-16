/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_exception_pipe_cat2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:51:20 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/13 19:00:11 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token		*ft_simplify_cat_pipes(t_minishell *ms, t_token *tokens);
static int	ft_count_useless_cats(t_minishell *ms, t_token *tokens);
static void	ft_copy_without_useless_cats(t_minishell *ms,
				t_token *tokens, t_token *new_tokens);
static void	ft_copy_token(t_token *dest, t_token *src);

/**
 * @brief  Counts how many " | cat | " sequences exist in the token array.
 * 
 * This function scans the tokens and counts occurrences of " | cat | ".
 * 
 * @param  tokens  The token array to analyze.
 * @return int     Number of useless " | cat | " sequences found.
 */
static int	ft_count_useless_cats(t_minishell *ms, t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= ms->n_args - 2)
	{
		if (tokens[i].type == TKN_PIPE
			&& tokens[i + 1].type == TKN_CMD
			&& !ft_strcmp(tokens[i + 1].value, "cat")
			&& tokens[i + 2].type == TKN_PIPE)
		{
			count++;
			i += 2;
			continue ;
		}
		i++;
	}
	return (count);
}

/**
 * @brief  Copies a token from the original array to the new array.
 * 
 * This function duplicates the token's value and type, ensuring 
 * all relevant information is preserved.
 * 
 * @param  dest  Pointer to the destination token.
 * @param  src   Pointer to the source token.
 * @return void
 */
static void	ft_copy_token(t_token *dest, t_token *src)
{
	dest->value = ft_strdup(src->value);
	dest->type = src->type;
	if (src->old_value)
		dest->old_value = ft_strdup(src->old_value);
}

/**
 * @brief  Copies tokens while removing redundant " | cat | " sequences.
 * 
 * This function scans the original token array and eliminates unnecessary "cat"
 * commands that only serve to pass data through, keeping only needed pipes.
 * 
 * @param  ms          Pointer to the minishell structure.
 * @param  tokens      The original array of tokens.
 * @param  new_tokens  The new token array being built.
 * @return void
 */
static void	ft_copy_without_useless_cats(t_minishell *ms,
				t_token *tokens, t_token *new_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ms->n_args)
	{
		if (tokens[i].type == TKN_PIPE && tokens[i + 1].type == TKN_CMD
			&& !ft_strcmp(tokens[i + 1].value, "cat")
			&& tokens[i + 2].type == TKN_PIPE)
		{
			i += 2;
			continue ;
		}
		else
		{
			ft_copy_token(&new_tokens[j], &tokens[i]);
			j++;
		}
		i++;
	}
	new_tokens[j].type = TKN_NULL;
	new_tokens[j].value = NULL;
	ms->n_args = j;
}

/**
 * @brief  Creates a new token array, removing all " | cat | " sequences.
 * 
 * This function simplifies token sequences by eliminating redundant "cat"
 * pipes, making execution more efficient and preventing broken pipes.
 * 
 * @param  ms      Pointer to the minishell structure.
 * @param  tokens  The original array of tokens.
 * @return t_token* New token array without unnecessary " | cat | " sequences.
 */
t_token	*ft_simplify_cat_pipes(t_minishell *ms, t_token *tokens)
{
	int		useless_cats;
	t_token	*new_tokens;

	useless_cats = ft_count_useless_cats(ms, tokens);
	new_tokens = ft_calloc(sizeof(t_token),
			(ms->n_args - (useless_cats * 2)) + 1);
	if (!new_tokens)
		return (NULL);
	ft_copy_without_useless_cats(ms, tokens, new_tokens);
	ft_free_tokens(tokens);
	return (new_tokens);
}
