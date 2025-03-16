/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:18:39 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/11 06:31:10 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_builtin_echo(char **args);
static int	ft_check_valid_echo_opt(char *opt);

/**
 * @brief 		Check if arg from echo is a valid variation of -n
 * 
 * @param opt	Option that needs to be checked
 * @return int	1: is a valid variation of -n
 * 				0: is not
 */
static int	ft_check_valid_echo_opt(char *opt)
{
	int	i;

	i = 1;
	if (ft_strncmp(opt, "-n", 2) == 0)
	{
		while (opt[i])
		{
			if (opt[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

/**
 * @brief 	Builtin echo
 * 
 * @param 	args 	What should be written on the command line
 * @param 	ms	 	minishell struct pointer
 */
void	ft_builtin_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (args[i])
	{
		if (ft_check_valid_echo_opt(args[i]) == 0)
			break ;
		new_line = 0;
		i++;
	}
	ft_sleep();
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	ft_exit_code(EX_OK);
}
