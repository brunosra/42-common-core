/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_process_input_and_execute.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:04:02 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/10 08:05:20 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_process_input_and_execute(t_minishell *ms);
static int	ft_handle_and_tokenize_input(t_minishell *ms);

/**
 * @brief  Process the user input and execute commands.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int
 **        0 on successful execution
 **        1 on error
 */
int	ft_process_input_and_execute(t_minishell *ms)
{
	if (ft_handle_and_tokenize_input(ms))
	{
		if (ft_exit_code(-1) == 2)
			return (1);
		else
			return (ft_putstr_and_return("minishell: unclosed quotes\n", 1));
	}
	ft_trim_last_cat_sequence(ms);
	ms->ast_root = ft_parse_ast(ms->tokens);
	if (ms->ast_root)
		ft_finalize_execution(ms);
	return (0);
}

/**
 * @brief  Tokenize the user input and check for unclosed quotes.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int
 **        0 on success
 **        1 if there are unclosed quotes or other errors
 */
static int	ft_handle_and_tokenize_input(t_minishell *ms)
{
	if (ft_check_quotes(ms->input))
		return (1);
	ms->n_args = ft_count_args(ms->input, 0);
	if (ms->n_args == -1)
		return (1);
	ms->tokens = ft_tokenize_input(ms->input, ms->n_args, 0, 0);
	if (ms->tokens == NULL)
		return (1);
	ft_revalue_tkn_var(ms);
	ms->tokens = ft_handle_empty_tokens(ms->tokens);
	return (0);
}
