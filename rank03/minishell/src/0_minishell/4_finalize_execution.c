/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_finalize_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:22:33 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/13 01:10:20 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_finalize_execution(t_minishell *ms);
static void	ft_close_stdin_stdout(t_minishell *ms);
static void	ft_clean_stuck_cats(t_minishell *ms);
static void	ft_clean_stuck_cats_child(t_minishell *ms);

/**
 * @brief  Finalizes the execution process.
 * 
 * Ensures AST execution, restores input/output, handles pipes, and
 * cleans up stuck "cat" processes if necessary.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
void	ft_finalize_execution(t_minishell *ms)
{
	ms->status = ft_execute_ast(ms->ast_root, ms);
	if ((dup2(ms->save_stdin, STDIN_FILENO) == -1
			|| dup2(ms->save_stdout, STDOUT_FILENO) == -1)
		&& ms->in_pipe == false)
	{
		ft_close_stdin_stdout(ms);
		ft_perror("dup2", 1);
		return ;
	}
	if (ms->in_pipe == true)
		ms->in_pipe = false;
	else
		ft_close_stdin_stdout(ms);
	if (ms->status != 130)
		ft_clean_stuck_cats(ms);
}

/**
 * @brief  Close saved stdin and stdout file descriptors.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
static void	ft_close_stdin_stdout(t_minishell *ms)
{
	close(ms->save_stdin);
	close(ms->save_stdout);
}

/**
 * @brief  Handles stuck "cat" commands waiting for input.
 * 
 * Spawns a child process to handle stuck "cat" commands, allowing input
 * until the process is interrupted or completed.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
void	ft_clean_stuck_cats(t_minishell *ms)
{
	if (!ms->c_stuck_cats)
		return ;
	ft_create_pipe(ms);
	ms->pid = fork();
	if (ms->pid == -1)
		return ;
	ft_set_fork_signals();
	if (ms->pid == 0)
		ft_clean_stuck_cats_child(ms);
	close(ms->pipefd[1]);
	waitpid(ms->pid, &ms->status, 0);
	close(ms->pipefd[0]);
	ms->c_stuck_cats = 0;
}

/**
 * @brief  Handles the child process for cleaning stuck "cat" commands.
 * 
 * Reads input from the user in a loop and decrements stuck "cat" counter
 * until the input is terminated or finished.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
static void	ft_clean_stuck_cats_child(t_minishell *ms)
{
	char	*input;
	int		no_stop;

	no_stop = 0;
	ft_set_heredoc_signals();
	close(ms->pipefd[0]);
	if (ms->c_stuck_cats == -1)
		no_stop = 1;
	while (ms->c_stuck_cats || no_stop == 1)
	{
		rl_on_new_line();
		input = readline("");
		if (!input)
			exit(ft_free_ms(ms, true, true, 0));
		printf("%s", input);
		printf("\n");
		ms->c_stuck_cats--;
		free(input);
	}
	close(ms->pipefd[1]);
	exit(ft_free_ms(ms, true, true, 0));
}
