/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:19:06 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/11 01:36:58 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_check_quotes(char *str);
int			ft_count_args(char *str, int i);
int			ft_handle_quotes(char *str, int i, int *start, int *end);
static int	ft_skip_and_process(char *str, int i, char quote_type);
static int	ft_handle_argument(char *str, int i);

/**
 * @brief  Check if the input string contains unclosed quotes.
 * 
 * @param  str  Input string.
 * @return int
 **        0 if no unclosed quotes are found
 **        1 if unclosed quotes are detected
 */
int	ft_check_quotes(char *str)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = '\0';
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote_type == '\0')
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = '\0';
		i++;
	}
	if (quote_type != '\0')
		return (1);
	return (0);
}

/**
 * @brief  Count the number of arguments in the input string.
 * 
 * @param  str  Input string.
 * @return int
 **        Number of arguments found in the string.
 */
int	ft_count_args(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';'
			|| str[i] == '&')
		{
			i++;
			if (str[i] && str[i + 1] && (str[i] == '<' || str[i] == '>'
					|| str[i] == '&' || str[i] == '|'))
				i++;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = ft_handle_quotes(str, i, 0, 0);
		else
			i = ft_handle_argument(str, i);
		count++;
	}
	return (count);
}

/**
 * @brief  Handle quoted sections in the input string.
 * 
 * @param  str    Input string.
 * @param  i      Current index in the string.
 * @param  start  Pointer to store the start index of the quoted section.
 * @param  end    Pointer to store the end index of the quoted section.
 * @return int    Updated index after handling the quoted section.
 */
int	ft_handle_quotes(char *str, int i, int *start, int *end)
{
	char	quote_type;

	if (start)
		*start = i;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_type = str[i++];
			if (str[i] && str[i] == quote_type && i >= 2 && str[i - 2] != '$')
				i++;
			else
				i = ft_skip_and_process(str, i, quote_type);
			if (str[i] == ' ' || str[i] == '|' || str[i] == '>'
				|| str[i] == '<')
				break ;
		}
		else
			i++;
	}
	if (end)
		*end = i;
	return (i);
}

/**
 * @brief  Skip content within quotes and process the rest of the string.
 * 
 * @param  str          Input string.
 * @param  i            Current index in the string.
 * @param  quote_type   The type of quote (' or ").
 * @return int          Updated index after processing quotes.
 */
static int	ft_skip_and_process(char *str, int i, char quote_type)
{
	while (str[i] && str[i] != quote_type)
		i++;
	if (str[i] == quote_type)
		i++;
	if (str[i] == ' ' || str[i] == '\0')
		return (i);
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"'
		&& str[i] != '|' && str[i] != '>' && str[i] != '<')
		i++;
	return (i);
}

/**
 * @brief  Handle a non-quoted argument in the input string.
 * 
 * @param  str  Input string.
 * @param  i    Current index in the string.
 * @return int  Updated index after handling the argument.
 */
static int	ft_handle_argument(char *str, int i)
{
	char	quotes;

	quotes = '\0';
	while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && str[i] != ';' && str[i] != '&')
	{
		if ((str[i] == '\'' || str[i] == '"') && i > 0 && str[i - 1] == '=')
			quotes = str[i];
		i++;
		while (quotes && str[i] && str[i] != quotes)
			i++;
		quotes = '\0';
	}
	return (i);
}
