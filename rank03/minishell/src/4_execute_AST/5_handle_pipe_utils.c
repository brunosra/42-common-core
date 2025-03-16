/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_handle_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:35:12 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/09 08:24:10 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_create_pipe(t_minishell *ms);
int		ft_pipe_syntax_error(char *token, int code);
void	ft_handle_unfinished_pipe(t_minishell *ms, char *input);
int		ft_handle_fork_error(void);

/**
 * @brief  Creates a pipe for heredoc input.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  0 on success, 1 on failure.
 */
int	ft_create_pipe(t_minishell *ms)
{
	if (pipe(ms->pipefd) == -1)
	{
		perror("pipe");
		ft_exit_code(1);
		return (1);
	}
	return (0);
}

/**
 * @brief  Prints a syntax error message for pipes and sets the exit code.
 * 
 * @param  ms     Pointer to the minishell structure.
 * @param  token  The unexpected token causing the error.
 * @param  code   Exit code to set.
 * @return int    Always returns 1.
 */
int	ft_pipe_syntax_error(char *token, int code)
{
	ft_putstr_three_fd("minishell: syntax error near unexpected token `", token,
		"'\n", STDERR_FILENO);
	ft_exit_code(code);
	return (1);
}

/**
 * @brief  Handles input continuation when the pipe is unfinished.
 * 
 * @param  ms     Pointer to the minishell structure.
 * @param  input  User input after an unfinished pipe.
 */
void	ft_handle_unfinished_pipe(t_minishell *ms, char *input)
{
	char	*temp;

	temp = ft_strjoin(ms->input, " ");
	free(ms->input);
	ms->input = ft_strjoin(temp, input);
	free(input);
	free(temp);
	ft_free_tokens(ms->tokens);
	ft_free_ast(ms->ast_root);
	ms->in_pipe = true;
}

/**
 * @brief  Handles fork errors.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int Always returns 1.
 */
int	ft_handle_fork_error(void)
{
	perror("fork");
	ft_exit_code(1);
	return (1);
}
