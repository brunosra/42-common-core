/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_if_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:06:35 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 02:35:38 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_check_if_expand(char *str, char *ptr, int heredoc);
int			ft_verify_quotes(char *quote_type, char c);
static int	ft_check_expansion_conditions(char *str, int i, int heredoc,
				char quote_type);
static int	ft_is_invalid_dollar_char(char c);

/**
 * @brief  Determines if a `$` should be expanded in a given string.
 * 
 * @param  str      The input string containing `$`.
 * @param  ptr      Pointer to the `$` character in the string.
 * @param  heredoc  Indicates if the function is being called inside a heredoc.
 * @return int      Expansion status.
 **         0 if the `$` should not be expanded.
 **         1 if it should be replaced with an environment variable.
 **         2 if it represents `$?` (exit status).
 */
int	ft_check_if_expand(char *str, char *ptr, int heredoc)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = '\0';
	while (str[i])
	{
		if (ft_verify_quotes(&quote_type, str[i]))
		{
			i++;
			continue ;
		}
		if (&str[i] == ptr)
			return (ft_check_expansion_conditions(str, i, heredoc, quote_type));
		i++;
	}
	return (0);
}

/**
 * @brief  Handles quote state changes in the input string.
 * 
 * @param  quote_type  Pointer to the current active quote type.
 * @param  c          The current character in the string.
 * @return int        1 if the character is a quote, 0 otherwise.
 */
int	ft_verify_quotes(char *quote_type, char c)
{
	if (c == '"' || c == '\'')
	{
		if (*quote_type == c)
			*quote_type = '\0';
		else if (*quote_type == '\0')
			*quote_type = c;
		return (1);
	}
	return (0);
}

/**
 * @brief  Determines whether a `$` should be expanded based on context.
 * 
 * @param  str        The input string.
 * @param  i          Index of the `$` character.
 * @param  heredoc    Whether the function is being called inside a heredoc.
 * @param  quote_type Current active quote type.
 * @return int        Expansion status.
 */
static int	ft_check_expansion_conditions(char *str, int i, int heredoc,
				char quote_type)
{
	if (str[i + 1] == '\'' || str[i + 1] == '"')
	{
		if (ft_check_balanced_quotes(str, i))
			return (1);
		return (0);
	}
	if (quote_type == '\'' && !heredoc)
		return (0);
	if (str[i + 1] == '?')
		return (2);
	if (ft_is_invalid_dollar_char(str[i + 1]))
		return (0);
	return (1);
}

/**
 * @brief  Checks if the character after `$` is an invalid expansion character.
 * 
 * @param  c  The character after `$`.
 * @return int  1 if the character is invalid for expansion, 0 otherwise.
 */
static int	ft_is_invalid_dollar_char(char c)
{
	return (!c || c == ' ' || c == '$' || c == '.' || c == ',' || c == '!'
		|| c == '?' || c == ';' || c == ':' || c == '~' || c == '^'
		|| c == '-' || c == '+' || c == '*' || c == '/');
}
