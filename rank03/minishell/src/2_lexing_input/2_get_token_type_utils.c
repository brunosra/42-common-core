/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_get_token_type_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:57:13 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/02/27 00:33:25 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_builtins(char *str);
int	ft_verify_variable_value(char *str, int i);

/**
 * @brief  Checks if a string corresponds to a supported builtin command.
 * 
 * @param  str  Command string to check.
 * @return int
 **        1 if the command is a builtin.
 **        0 otherwise.
 */
int	ft_check_builtins(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

/**
 * @brief  Verifies whether a variable within a string should be expanded.
 * 
 * @param  str  Input string.
 * @param  i  Index. 
 * @return int
 **        1 if the variable should be expanded.
 **        0 otherwise.
 */
int	ft_verify_variable_value(char *str, int i)
{
	char	quote_type;
	int		expand;

	quote_type = '\0';
	expand = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\''))
		{
			if (quote_type == str[i])
				quote_type = '\0';
			else if (quote_type == '\0')
				quote_type = str[i];
			i++;
			continue ;
		}
		if (str[i] == '$')
		{
			if (quote_type != '\'')
				expand = 1;
		}
		i++;
	}
	return (expand);
}
