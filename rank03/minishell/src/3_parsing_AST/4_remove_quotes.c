/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_remove_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:59:02 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/28 05:12:10 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*ft_remove_quotes(char *value);
static void	ft_concat_new_value(char **final, char *sub);
static char	*ft_extract_unquoted(char *value, int *index);
static char	*ft_extract_quoted(char *value, int *index, char quote_type);

/**
 * @brief  Removes quotes from a given string and returns the updated value.
 * 
 * @param  value  String to process and remove quotes from.
 * @return char*  Processed string with quotes removed.
 */
char	*ft_remove_quotes(char *value)
{
	int		i;
	char	*final;
	char	*sub;

	i = 0;
	final = NULL;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			sub = ft_extract_quoted(value, &i, value[i]);
		else
			sub = ft_extract_unquoted(value, &i);
		if (!sub)
		{
			free(final);
			free(value);
			return (NULL);
		}
		ft_concat_new_value(&final, sub);
	}
	free(value);
	return (final);
}

/**
 * @brief  Extracts a substring between matching quotes.
 * 
 * @param  value       Input string containing quotes.
 * @param  index       Pointer to current position in string.
 * @param  quote_type  Type of quote (' or ").
 * @return char*       Extracted substring without quotes.
 */
static char	*ft_extract_quoted(char *value, int *index, char quote_type)
{
	int		start;
	char	*sub;

	start = ++(*index);
	while (value[*index] && value[*index] != quote_type)
		(*index)++;
	sub = ft_substr(value, start, *index - start);
	if (value[*index])
		(*index)++;
	return (sub);
}

/**
 * @brief  Extracts a substring without quotes.
 * 
 * @param  value  Input string.
 * @param  index  Pointer to current position in string.
 * @return char*  Extracted substring.
 */
static char	*ft_extract_unquoted(char *value, int *index)
{
	int		start;

	start = *index;
	while (value[*index] && value[*index] != '\'' && value[*index] != '\"')
		(*index)++;
	return (ft_substr(value, start, *index - start));
}

/**
 * @brief  Concatenates a new substring to the final string.
 * 
 * @param  final  Pointer to the final string.
 * @param  sub    Substring to append.
 */
static void	ft_concat_new_value(char **final, char *sub)
{
	char	*temp;

	if (!sub)
		return ;
	if (!*final)
	{
		*final = ft_strdup(sub);
		if (!*final)
			free(sub);
	}
	else
	{
		temp = ft_strjoin(*final, sub);
		if (!temp)
		{
			free(sub);
			return ;
		}
		free(*final);
		*final = temp;
	}
	free(sub);
}
