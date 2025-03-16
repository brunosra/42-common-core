/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:48:34 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/07 18:12:47 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_type			ft_get_token_type(char *str, t_type prev_type);
static t_type	ft_check_redirection_and_operator(char *str, t_type prev_type,
					bool *inverted);
static t_type	ft_check_redirection(char *str);
static t_type	ft_check_operator_or_exception(char *str);
static t_type	ft_check_variable(char *str);

/**
* @brief  Determines the type of a token based on its value and previous token.
* 
* @param  str        Token value.
* @param  prev_type  Previous token type.
* @return t_type     Token type.
*/
t_type	ft_get_token_type(char *str, t_type prev_type)
{
	t_type			type;
	static bool		inverted = false;

	type = ft_check_redirection_and_operator(str, prev_type, &inverted);
	if (type != TKN_CMD)
		return (type);
	if (prev_type == TKN_NULL || prev_type == TKN_PIPE
		|| (prev_type == TKN_FILE && inverted == true))
	{
		inverted = false;
		if (ft_check_builtins(str))
			return (TKN_BLTIN);
		return (TKN_CMD);
	}
	if (str && (str[0] == '$' || ft_strchr(str, '$')))
		return (ft_check_variable(str));
	if ((str[0] == '"' || str[0] == '\'') && (prev_type != TKN_CMD
			&& prev_type != TKN_BLTIN && prev_type != TKN_VAR
			&& prev_type != TKN_PIPE && prev_type != TKN_EXCPT
			&& prev_type != TKN_ARG && prev_type != TKN_FILE))
		return (TKN_FILE);
	if (prev_type == TKN_CMD || prev_type == TKN_BLTIN || prev_type == TKN_ARG
		|| prev_type == TKN_VAR || prev_type == TKN_FILE)
		return (TKN_ARG);
	return (TKN_CMD);
}

/**
 * @brief  Handles redirection and operator token types.
 * 
 * @param  str        Token value.
 * @param  prev_type  Previous token type.
 * @param  inverted   Pointer to the static boolean flag.
 * @return t_type     Token type.
 */
static t_type	ft_check_redirection_and_operator(char *str, t_type prev_type,
	bool *inverted)
{
	t_type	type;

	type = ft_check_redirection(str);
	if ((type == TKN_OUT_RD || type == TKN_HDOC || type == TKN_IN_RD)
		&& (prev_type == TKN_PIPE || prev_type == TKN_NULL))
		*inverted = true;
	if (type != TKN_CMD)
		return (type);
	if (prev_type == TKN_OUT_RD || prev_type == TKN_IN_RD
		|| prev_type == TKN_HDOC)
		return (TKN_FILE);
	type = ft_check_operator_or_exception(str);
	if (type == TKN_PIPE && (prev_type == TKN_PIPE || prev_type == TKN_EXCPT))
		return (TKN_EXCPT);
	return (type);
}

/**
 * @brief Checks if the token is a redirection operator.
 * 
 * @param str Token value.
 * @return t_type Corresponding token type or TKN_CMD.
 */
static t_type	ft_check_redirection(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (TKN_IN_RD);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, ">|"))
		return (TKN_OUT_RD);
	else if (!ft_strcmp(str, "<<"))
		return (TKN_HDOC);
	return (TKN_CMD);
}

/**
 * @brief Checks if the token is an operator or exception type.
 * 
 * @param str Token value.
 * @return t_type Corresponding token type or TKN_CMD.
 */
static t_type	ft_check_operator_or_exception(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TKN_PIPE);
	else if (!ft_strcmp(str, "||") || !ft_strcmp(str, "&&")
		|| !ft_strcmp(str, ";") || !ft_strcmp(str, "&")
		|| str[0] == ';' || str[0] == '&' || (str[0] == '|' && str[1]))
		return (TKN_EXCPT);
	return (TKN_CMD);
}

/**
 * @brief Determines if the token is a variable or filename type.
 * 
 * @param str       Token value.
 * @param prev_type Previous token type.
 * @return t_type Corresponding token type or TKN_ARG.
 */
static t_type	ft_check_variable(char *str)
{
	if (str[0] == '$')
		return (TKN_VAR);
	if (ft_verify_variable_value(str, 0))
		return (TKN_VAR);
	return (TKN_ARG);
}
