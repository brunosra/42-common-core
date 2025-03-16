/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:13:47 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/06 04:51:38 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_builtin_export_check(char **args);
void		ft_builtin_export(char **args, t_minishell *ms);
static void	ft_validate_and_process_export(char **args, t_minishell *ms);
static int	ft_export_1_arg(t_minishell *ms);
int			ft_valid_export_arg(const char *arg);

/**
 * @brief  Counts the number of arguments passed to the export command.
 * 
 * @param  args  Pointer to the array of arguments.
 * @return int   Number of arguments.
 */
int	ft_builtin_export_check(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (0);
}

/**
 * @brief  Handles the `export` command, either printing or adding variables.
 * 
 * @param  args  The command arguments.
 * @param  ms    Pointer to the minishell structure.
 */
void	ft_builtin_export(char **args, t_minishell *ms)
{
	if (ms->env.export == NULL)
	{
		ms->env.export = ft_duplicate_envp(ms->env.envp);
		if (ms->env.export == NULL)
			ft_perror("malloc", ft_exit_code(1));
	}
	if (args[1] == NULL)
		ft_export_1_arg(ms);
	else
		ft_validate_and_process_export(args, ms);
}

/**
 * @brief  Validates and processes all export arguments.
 * 
 * @param  args  Array of export arguments.
 * @param  ms    Pointer to the minishell structure.
 */
void	ft_validate_and_process_export(char **args, t_minishell *ms)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i])
	{
		if (ft_valid_export_arg(args[i]) == 0)
			error = ft_putstr_three_fd("minishell: export: `", args[i],
					"': not a valid identifier\n", STDERR_FILENO);
		else
			ft_process_export(args[i], ms);
		i++;
	}
	ft_exit_code(error);
}

/**
 * @brief  Validates if a given argument is a valid export variable name.
 * 
 * @param  arg  The variable name to validate.
 * @return int  1 if valid, 0 otherwise.
 */
int	ft_valid_export_arg(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!((arg[0] >= 'A' && arg[0] <= 'Z')
			|| (arg[0] >= 'a' && arg[0] <= 'z')
			|| (arg[0] == '_')))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!((arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (arg[i] >= '0' && arg[i] <= '9')
				|| (arg[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief  Handles `export` when called without arguments, printing variables.
 * 
 * @param  ms  Pointer to the minishell structure.
 * @return int  Exit code.
 */
static int	ft_export_1_arg(t_minishell *ms)
{
	int	count;

	count = -1;
	while (ms->env.export[++count] != NULL)
		;
	ft_sort_envp(ms->env.export, count);
	ft_output_export_1_arg(ms->env.export, count);
	return (ft_exit_code(0));
}
