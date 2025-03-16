/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:47:54 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/06 04:51:53 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int					ft_builtin_exit(char **args);
static int			ft_value_is_numeric(char *str);
static long long	ft_atoll(char *str, int i, long long res);
static void			ft_putstr_and_exit(char *str);

/**
 * @brief	Implement the `exit` builtin command.
 * 
 * @param	args	Array of arguments passed to the `exit` command.
 * @return	int
 * 			Exit code to be used when terminating the shell.
 * 
 * @details
 * - No arguments: Returns 0, indicating a successful exit.
 * - Single argument: Converts the argument to a numeric exit code modulo 256.
 * - Multiple arguments: Prints an error message for too
 * 						 many arguments and returns 1.
 * - Non-numeric argument: Prints an error message and returns 2.
 */
int	ft_builtin_exit(char **args)
{
	int	mod;
	int	i;

	mod = 0;
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		(ft_exit_code(-1));
	else if (i > 2 && ft_atoll(args[1], 0, 0))
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n",
			STDERR_FILENO);
		return (ft_exit_code(1));
	}
	else if (ft_value_is_numeric(args[1]))
	{
		mod = ft_atoll(args[1], 0, 0) % 256;
		ft_exit_code(mod);
	}
	else if (!ft_value_is_numeric(args[1]))
		ft_putstr_and_exit(args[1]);
	ft_free_ms(ft_ms_struct(NULL, 1), true, true, 0);
	exit(ft_exit_code(-1));
	return (0);
}

/**
 * @brief	Check if a string contains numeric characters.
 * 
 * @param	str	String to check for numeric characters.
 * @return	int
 * 			1 if the string contains numeric characters, 0 otherwise.
 */
static int	ft_value_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief  Prints an exit error message and terminates the shell.
 * 
 * @param  str  The invalid argument that caused the exit error.
 * @return void This function does not return; it calls exit(2).
 */
static void	ft_putstr_and_exit(char *str)
{
	ft_putstr_three_fd("exit\nminishell: exit: ", str,
		": numeric argument required\n", STDERR_FILENO);
	ft_free_ms(ft_ms_struct(NULL, 1), true, true, 0);
	exit(2);
}

/**
 * @brief	Convert a string to a long long integer with error handling.
 * 
 * @param	str	String to be converted.
 * @param	i	Initial offset in the string for conversion.
 * @param	res	Initial value to use for the result (typically 0).
 * @return	long long
 * 			The converted value as a signed long long integer.
 * 
 * @details
 * - Handles leading whitespace and optional '+' or '-' signs.
 * - Detects overflow or invalid characters in the input string.
 * - Prints an error message and exits with code 2 if
 * 	 the string is not numeric or overflows.
 */
static long long	ft_atoll(char *str, int i, long long res)
{
	int	sig;

	sig = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sig = -1;
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (res > (LLONG_MAX / 10) || (res == LLONG_MAX / 10
					&& (str[i] - '0') > (LLONG_MAX % 10)))
				ft_putstr_and_exit(str);
			res = res * 10 + (str[i] - '0');
			i++;
		}
		if (str[i] != '\0')
			ft_putstr_and_exit(str);
	}
	else
		ft_putstr_and_exit(str);
	return (res * sig);
}
