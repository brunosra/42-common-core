/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_remove_null_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 02:02:16 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 00:47:00 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		**ft_remove_null_values(char **cmd_ready, int arg_count);
static void	ft_copy_valid_args(char **cmd_ready, char **new_cmd_ready,
				int valid_count);
static int	ft_count_valid_args(char **cmd_ready);

/**
 * @brief  Removes null or empty values from a command's arguments array.
 * 
 * @param  cmd_ready  Array of command arguments.
 * @param  arg_count  Total number of arguments.
 * @return char**     Updated array without null or empty values.
 */
char	**ft_remove_null_values(char **cmd_ready, int arg_count)
{
	char	**new_cmd_ready;
	int		valid_count;

	valid_count = ft_count_valid_args(cmd_ready);
	if (valid_count == arg_count)
		return (cmd_ready);
	new_cmd_ready = malloc(sizeof(char *) * (valid_count + 1));
	if (!new_cmd_ready)
		return (cmd_ready);
	ft_copy_valid_args(cmd_ready, new_cmd_ready, valid_count);
	if (*cmd_ready)
		ft_free_split(cmd_ready);
	return (new_cmd_ready);
}

/**
 * @brief  Counts the number of valid (non-null, non-empty) values in cmd_ready.
 * 
 * @param  cmd_ready  Array of command arguments.
 * @return int        Number of valid arguments.
 */
static int	ft_count_valid_args(char **cmd_ready)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd_ready[i])
	{
		if (cmd_ready[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief  Copies valid arguments into a new allocated array.
 * 
 * @param  cmd_ready      Array of command arguments.
 * @param  new_cmd_ready  New allocated array for valid arguments.
 * @param  valid_count    Number of valid arguments.
 */
static void	ft_copy_valid_args(char **cmd_ready, char **new_cmd_ready,
								int valid_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (valid_count > 0)
	{
		if (cmd_ready[i][0] != '\0')
		{
			new_cmd_ready[j] = ft_strdup(cmd_ready[i]);
			j++;
			valid_count--;
		}
		i++;
	}
	new_cmd_ready[j] = NULL;
}
