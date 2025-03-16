/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:28:29 by bschwell          #+#    #+#             */
/*   Updated: 2025/02/27 18:03:46 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_builtin_env(char **args, t_minishell *ms);

/**
 * @brief		Implements the `env` builtin command, printing the
 * 				environment variables.
 * 
 * @param  args	Arguments passed to the `env` command. Should be NULL or
 * 				a single argument.
 * @param  ms	Pointer to the minishell structure containing the environment
 * 				variables.
 * @return		void
 * 
 * @details
 *         		- If additional arguments are provided, an error message is
 * 				  printed, and the exit code is set to EX_EXITARGERR.
 *         		- If no arguments are provided, all environment variables
 * 				  are printed, one per line.
 *         		- The exit code is set to EX_OK upon successful execution.
 */
void	ft_builtin_env(char **args, t_minishell *ms)
{
	char	**env;

	env = ms->env.envp;
	if (args[1])
	{
		printf("env: ‘%s’: No such file or directory\n", args[1]);
		ft_exit_code(EX_NOTFOUNDERR);
		return ;
	}
	else
	{
		while (*env != 0)
		{
			printf("%s\n", *env);
			env++;
		}
	}
	ft_exit_code(EX_OK);
}
