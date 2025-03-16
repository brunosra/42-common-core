/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_remove_extra_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:16:59 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/05 20:31:00 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_remove_extra_spaces(char **str);
static int	ft_count_non_space_chars(char *str);
static char	*ft_create_trimmed_string(char *str, int count);

/**
 * @brief  Removes extra spaces from the given string and replaces it.
 * 
 * @param str The input string, which will be replaced with the trimmed version.
 */
int	ft_remove_extra_spaces(char **str)
{
	size_t	count;
	char	*new_str;

	new_str = NULL;
	if (!str || !*str)
		return (1);
	count = ft_count_non_space_chars(*str);
	if (count == ft_strlen(*str))
		return (1);
	new_str = ft_create_trimmed_string(*str, count);
	if (!new_str)
		return (1);
	*str = new_str;
	return (0);
}

/**
 * @brief  Counts the number of non-space characters in the string.
 * 
 * @param  str  The input string.
 * @return int  The number of non-space characters.
 */
static int	ft_count_non_space_chars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			count++;
			i++;
		}
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
			if (!str[i])
				count--;
		}
	}
	return (count);
}

/**
 * @brief  Allocates and creates a new string without extra spaces.
 * 
 * @param  str  The input string.
 * @param  count  The length of the new string.
 * @return char*  The new string without extra spaces.
 */
static char	*ft_create_trimmed_string(char *str, int count)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = ft_calloc(sizeof(char), (count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			new_str[j++] = str[i++];
		}
		if (str[i] == ' ')
			new_str[j++] = ' ';
	}
	if (j > 0 && new_str[j - 1] == ' ')
		j--;
	new_str[j] = '\0';
	return (new_str);
}
