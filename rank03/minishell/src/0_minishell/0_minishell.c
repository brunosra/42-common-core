/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:48:24 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/14 04:15:17 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			main(int argc, char **argv, char **envp);
static void	ft_init_ms(t_minishell *ms);
static int	ft_save_stdin_stdout(t_minishell *ms);
static int	ft_readline(t_minishell *ms);
void		ft_create_prompt(t_minishell *ms);

/**
 * @brief  Main entry point of the program.
 * 
 * @param  argc  Argument count (unused).
 * @param  argv  Argument vector (unused).
 * @param  envp  Environment variables.
 * @return int
 **        Exit code of the shell
 */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argv;
	(void)argc;
	ft_init_ms(&ms);
	ms.env.envp = ft_duplicate_envp(envp);
	if (!ms.env.envp)
		return (ft_perror("malloc", 1));
	while (1)
	{
		ft_set_main_signals();
		ft_ms_struct(&ms, 0);
		if (ft_save_stdin_stdout(&ms))
			return (1);
		if (ft_readline(&ms))
			break ;
		if (ft_process_input_and_execute(&ms))
			continue ;
		ft_free_ms(&ms, false, false, 0);
	}
	ft_free_split(ms.env.envp);
	ft_free_split(ms.env.export);
	return (ft_exit_code(-1));
}

/**
 * @brief  Initialize the minishell structure with default values.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return void
 */
static void	ft_init_ms(t_minishell *ms)
{
	ms->input = NULL;
	ms->tokens = NULL;
	ms->temp = NULL;
	ms->status = -1;
	ms->save_stdin = -1;
	ms->save_stdout = -1;
	ms->n_args = -1;
	ms->pid = -1;
	ms->c_multi_heredocs = 0;
	ms->c_stuck_cats = 0;
	ms->pipefd[0] = -1;
	ms->pipefd[1] = -1;
	ms->swap_input_redirects = false;
	ms->swap_output_redirects = false;
	ms->in_pipe = false;
	ms->env.envp = NULL;
	ms->env.env_paths = NULL;
	ms->env.paths = NULL;
	ms->env.full_path = NULL;
	ms->env.export = NULL;
	ms->prompt = NULL;
	ms->error_files = NULL;
}

/**
 * @brief  Save the current stdin and stdout file descriptors.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int
 **        0 on success
 **        1 if an error occurs during duplication
 */
static int	ft_save_stdin_stdout(t_minishell *ms)
{
	ms->save_stdin = dup(STDIN_FILENO);
	ms->save_stdout = dup(STDOUT_FILENO);
	if (ms->save_stdin == -1 || ms->save_stdout == -1)
		return (ft_perror("dup", 1));
	return (0);
}

/**
 * @brief  Read a line of input using readline and handle the prompt display.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int
 **        0 on successful input
 **        1 if the input is NULL (EOF or Ctrl-D)
 */
static int	ft_readline(t_minishell *ms)
{
	ms->swap_output_redirects = false;
	ms->swap_input_redirects = false;
	ms->c_stuck_cats = 0;
	ms->error_files = NULL;
	rl_on_new_line();
	ft_create_prompt(ms);
	ms->input = readline(ms->prompt);
	if (ms->input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		free(ms->prompt);
		return (1);
	}
	if (ms->input && ms->input[0] != '\0')
		add_history(ms->input);
	return (0);
}

/**
 * @brief  Constructs a new prompt string for the minishell.
 * 
 * This function dynamically creates a new prompt string for the minishell by 
 * combining the current exit code, the current working directory, and a fixed 
 * prompt format. The exit code is displayed within square brackets, followed by 
 * the current directory, and a fixed "minishell" label, with each component in 
 * specific colors. The prompt is then updated within the minishell structure.
 * 
 * The colors used are:
 * - Exit code: Green
 * - Current directory: Yellow
 * - The label "minishell": Red
 * - Prompt symbol "$": White
 * 
 * @param  ms  Pointer to the ms structure which contains the current prompt.
 * @return void
 * 
 * @note for exit_code in propmt @include / @replace:
 * 	char	*e;
 * 	e = ft_itoa(ft_exit_code(-1));
 * 	new_prompt = ft_strjoin_all(7, "\001\e[32m\002[", e, "\001\e[32m\002]",
			"\001\e[33m\002[", p, "\001\e[33m\002]\001\e[31m\002minishell",
			"\001\e[37m\002$ "); 
 *  fee(e);
 *	@see also handel_sihnal.c >> void	ft_signal_handler(int sig)
 */
void	ft_create_prompt(t_minishell *ms)
{
	char	*old_prompt;
	char	*new_prompt;
	char	p[PATH_MAX];

	getcwd(p, PATH_MAX);
	old_prompt = ms->prompt;
	new_prompt = ft_strjoin_all(4, "\001\e[36m\002minishell:", "\001\e[33m\002",
			p, "\001\e[37m\002$ ");
	free(old_prompt);
	ms->prompt = new_prompt;
}
