/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:24:29 by bschwell          #+#    #+#             */
/*   Updated: 2025/03/03 01:11:42 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_dup_envp(char **envp, char ***dupenv, int count);
void	ft_output_export_1_arg(char **arr, int count);
int		ft_sort_envp(char **dupenv, int count);
void	ft_swap(char **a, char **b);
void	ft_free_str_arr(char **arr);

/**
 * @brief	Duplicates a given array of environment variables.
 * 
 * @param	src		Source array of strings to be duplicated.
 * @param	dest	Destination array to store the duplicated strings.
 * @param	count	Number of strings in the source array to duplicate.
 * 
 * @details
 * - Allocates memory for each string in the destination array.
 * - Copies the content of each string from the source array
 * 	 to the destination array.
 * - Adds a NULL terminator at the end of the destination array.
 * - Exits the program if memory allocation fails.
 */
int	ft_dup_envp(char **envp, char ***dupenv, int count)
{
	int	i;

	i = 0;
	if (*dupenv)
		free(*dupenv);
	*dupenv = malloc((count + 1) * sizeof(char *));
	if (!(*dupenv))
		return (-1);
	while (i < count)
	{
		(*dupenv)[i] = ft_strdup(envp[i]);
		if (!(*dupenv)[i])
		{
			while (i > 0)
			{
				i--;
				free((*dupenv)[i]);
			}
			free(*dupenv);
			return (-1);
		}
		i++;
	}
	(*dupenv)[count] = NULL;
	return (0);
}

/**
 * @brief 		Handles the output of the export command
 * 				removes the last _ variable from the output
 * 
 * @param arr 	arr of duplicated envps
 * @param count counted how many vars
 */
void	ft_output_export_1_arg(char **arr, int count)
{
	int		i;

	i = -1;
	if (arr == NULL)
	{
		printf("[print_str_arr]: NULL / Empty array");
		return ;
	}
	while (++i < count)
	{
		if (ft_strncmp(arr[i], "_=", 2) == 0
			|| ft_strcmp(arr[i], "_") == 0)
			continue ;
		printf("declare -x %s\n", arr[i]);
	}
}

/**
 * @brief	Sorts an array of environment variable strings in alphabetical order.
 * 
 * @param	arr		Array of strings to be sorted.
 * @param	count	Number of strings in the array.
 * 
 * @details
 * - Implements a bubble sort algorithm to sort the strings lexicographically.
 * - Swaps adjacent strings if they are out of order.
 * - Uses `ft_strcmp` to compare the strings.
 */
int	ft_sort_envp(char **dupenv, int count)
{
	int	swapped;
	int	i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(dupenv[i], dupenv[i + 1]) > 0)
			{
				ft_swap(&dupenv[i], &dupenv[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return (0);
}

/**
 * @brief	Swaps the values of two environment variable pointers.
 * 
 * @param	a	Pointer to the first string to be swapped.
 * @param	b	Pointer to the second string to be swapped.
 * 
 * @details
 * - Swaps the values of the two pointers using a temporary variable.
 */
void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief	Frees the memory allocated for a duplicated
 * 			environment variable array.
 * 
 * @param	arr	Array of strings to be freed.
 * 
 * @details
 * - Frees each string in the array.
 * - Frees the array pointer itself.
 * - Does nothing if the array is NULL.
 */
void	ft_free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
