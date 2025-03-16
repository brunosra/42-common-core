/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_revalue_quoted_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:07:37 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 00:33:53 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*ft_revalue_quoted_value(char *value);
static char	*ft_process_quoted_segment(char *value, int *i);
static char	*ft_process_unquoted_segment(char *value, int *i);
static void	ft_append_to_final(char **final, char *segment);

/**
 * @brief Processes a string containing quoted and unquoted segments,
 * removing quotes and combining parts.
 * 
 * @param value Original string to process.
 * @return char* Processed string with quotes removed.
 */
char	*ft_revalue_quoted_value(char *value)
{
	int		i;
	char	*final;
	char	*segment;

	i = 0;
	final = NULL;
	if (!value)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '"' || value[i] == '\'')
			segment = ft_process_quoted_segment(value, &i);
		else
			segment = ft_process_unquoted_segment(value, &i);
		ft_append_to_final(&final, segment);
	}
	free(value);
	return (final);
}

/**
 * @brief Processes and extracts a quoted substring from a given value.
 * 
 * @param value Original string containing quotes.
 * @param i Current index position within the string.
 * @return char* The processed substring inside the quotes.
 */
static char	*ft_process_quoted_segment(char *value, int *i)
{
	char	quote_type;
	char	*start;
	char	*end;
	char	*arg;

	quote_type = value[*i];
	start = &value[*i];
	(*i)++;
	if (value[*i] == quote_type)
	{
		(*i)++;
		return (ft_strdup(""));
	}
	while (value[*i] && value[*i] != quote_type)
		(*i)++;
	if (value[*i] == quote_type)
		(*i)++;
	end = &value[*i];
	arg = ft_substr(value, start - value, end - start);
	return (arg);
}

/**
 * @brief Processes and extracts a substring outside of quotes.
 * 
 * @param value Original string.
 * @param i Current index position within the string.
 * @return char* The processed substring outside of the quotes.
 */
static char	*ft_process_unquoted_segment(char *value, int *i)
{
	char	*start;
	char	*end;
	char	*arg;

	start = &value[*i];
	while (value[*i] && value[*i] != '"' && value[*i] != '\'')
		(*i)++;
	end = &value[*i];
	arg = ft_substr(value, start - value, end - start);
	return (arg);
}

/**
 * @brief Appends a segment to the final string, handling memory management.
 * 
 * @param final Pointer to the final result string.
 * @param segment The segment to append.
 */
static void	ft_append_to_final(char **final, char *segment)
{
	char	*temp;

	if (!(*final))
		*final = ft_strdup(segment);
	else
	{
		temp = *final;
		*final = ft_strjoin(*final, segment);
		free(temp);
	}
	free(segment);
}
